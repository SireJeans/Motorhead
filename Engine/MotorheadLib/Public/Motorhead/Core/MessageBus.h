#pragma once

#include "StdIncludes.h"

#include "PrimitiveTypes.h"
#include "Containers.h"
#include "SmartPointer.h"
#include "Delegate.h"

namespace motor::core {

    struct Message
    {
        using id = sizeT;

        template<typename T>
        static id Id();
    };

    template<typename T>
    Message::id Message::Id()
    {
        std::type_index idx = typeid(T);
        return sizeT{ idx.hash_code() };
    }

    struct MessageContainerBase
    {
        MessageContainerBase() = default;
        MessageContainerBase(MessageContainerBase&&) = default;
        MessageContainerBase(const MessageContainerBase&) = default;
        MessageContainerBase& operator =(MessageContainerBase&&) = default;
        MessageContainerBase& operator =(const MessageContainerBase&) = default;
        virtual ~MessageContainerBase() = default;

        [[nodiscard]] virtual sizeT Size() const = 0;
        virtual void Remove(sizeT index) = 0;
        [[nodiscard]] virtual bool Validate(sizeT index) const = 0;
    };

    template<typename M>
    class MessageContainer final : public MessageContainerBase
    {
    public:
        MessageContainer() = default;
        MessageContainer(MessageContainer&&) = default;
        MessageContainer(const MessageContainer&) = default;
        MessageContainer& operator =(MessageContainer&&) = default;
        MessageContainer& operator =(const MessageContainer&) = default;
        ~MessageContainer() = default;

        [[nodiscard]] sizeT Size() const override final;
        void Remove(sizeT index) override final;
        [[nodiscard]] bool Validate(sizeT index) const override final;

        //sizeT Add(std::function<void(M)> subscriber);
        sizeT Add(core::Delegate<void(M)> subscriber);
        void Publish(M message);

    private:
        sizeT m_index = 0;
        //core::map<sizeT , std::function<void(M)>> m_subscribers;
        core::map<sizeT , core::Delegate<void(M)>> m_subscribers;
    };

    template<typename M>
    sizeT MessageContainer<M>::Size() const
    {
        return m_subscribers.size();
    }

    template<typename M>
    void MessageContainer<M>::Remove(sizeT index)
    {
        auto iterator = m_subscribers.find(index);

        if (iterator != m_subscribers.end())
        {
            m_subscribers.erase(iterator);
        }
    }

    template<typename M>
    bool MessageContainer<M>::Validate(sizeT index) const
    {
        return m_subscribers.find(index) != m_subscribers.end();
    }

    template<typename M>
    //sizeT MessageContainer<M>::Add(std::function<void(M)> subscriber)
    sizeT MessageContainer<M>::Add(core::Delegate<void(M)> subscriber)
    {
        m_subscribers.insert({ m_index, subscriber });
        ++m_index;
        return m_index - 1u;
    }

    template<typename M>
    void MessageContainer<M>::Publish(M message)
    {
        for (auto& subscriber : m_subscribers)
        {
            subscriber.second.Invoke(message);
        }
    }

    class SubscriberHandle
    {
    public:
        SubscriberHandle(Message::id id, sizeT index);

        [[nodiscard]] Message::id Id() const;
        [[nodiscard]] sizeT Index() const;

    private:
        Message::id m_id;
        sizeT m_index;
    };

    inline SubscriberHandle::SubscriberHandle(const Message::id id, const sizeT index)
        : m_id(id)
        , m_index(index)
    {

    }

    inline Message::id SubscriberHandle::Id() const
    {
        return m_id;
    }

    inline sizeT SubscriberHandle::Index() const
    {
        return m_index;
    }

    class MessageBus
    {
    public:
        template<typename M>
        SubscriberHandle Subscribe(core::Delegate<void(M)> subscriber);
        void Unsubscribe(SubscriberHandle& subscriber_handle);
        template<typename M>
        void Publish(M message);
        template<typename M>
        [[nodiscard]] bool Validate(SubscriberHandle handle) const;

    private:
        core::map<Message::id, core::UniquePtr<MessageContainerBase>> m_repository;
    };

    template<typename M>
    //SubscriberHandle MessageBus::Subscribe(std::function<void(M)> subscriber)
    SubscriberHandle MessageBus::Subscribe(core::Delegate<void(M)> subscriber)
    {
        auto repo = m_repository.find(Message::Id<M>());
        auto valid = true;
        auto index = std::size_t{ 0u };

        if (repo == m_repository.end())
        {
            auto result = m_repository.insert({ Message::Id<M>(), std::make_unique<MessageContainer<M>>() });
            valid = result.second;
            repo = result.first;
        }

        if (valid)
        {
            index = static_cast<MessageContainer<M>*>(repo->second.get())->Add(subscriber);
        }

        return SubscriberHandle{ Message::Id<M>(), index };
    }

    inline void MessageBus::Unsubscribe(SubscriberHandle& subscriber_handle)
    {
        auto repo = m_repository.find(subscriber_handle.Id());

        if (repo != m_repository.end())
        {
            repo->second->Remove(subscriber_handle.Index());
        }
    }

    template<typename M>
    void MessageBus::Publish(M message)
    {
        auto repo = m_repository.find(Message::Id<M>());

        if (repo != m_repository.end())
        {
            static_cast<MessageContainer<M>*>(repo->second.get())->Publish(message);
        }
    }

    template<typename M>
    bool MessageBus::Validate(SubscriberHandle handle) const
    {
        auto result = false;

        if (handle.Id() != Message::Id<M>())
        {
            return result;
        }

        auto repo = m_repository.find(Message::Id<M>());

        if (repo != m_repository.end())
        {
            result = repo->second->validate(handle.Index());
        }

        return result;
    }

}
