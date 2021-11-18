#pragma once


#include <Motorhead/Common.h>
#include "Motorhead/Core/BitOps.h"
#include "../Test.h"

using namespace motor;

struct TestStruct
{
	unint field0;
	unint field1;
	unint field2;
	unint field3;
};

class EngineTest : public Test {
public:
	bool Initialize() override {
		return true;
	}

	void Run() override {
		
		do {
			u32 bitfield1 = bits::Ops32::SetWordRange0(0xFFFFFFFF, 8, 8);
			u32 bitfield2 = bits::Ops32::SetWordRange0(0xFFFFFFFF, 0, 0);
			u32 bitfield3 = bits::Ops32::SetWordRange0(0xFFFFFFFF, 31, 1);
			u32* bitfield4 = &bitfield2;
			bits::Ops32::SetWordRange0(bitfield4, 8, 8);

			MH_GDEBUG("{:X}\n", bitfield1);
			MH_GDEBUG("{:X}\n", bitfield2);
			MH_GDEBUG("{:X}\n", bitfield3);

			bitfield1 = bits::Ops32::ClearLower(0xFFFFFFFF, 8);
			bitfield2 = bits::Ops32::ClearHigher(0xFFFFFFFF, 8);
			bitfield3 = 0xFFFFFFFF;
			u32 bitfield5 = 0xFFFFFFFF;
			bits::Ops32::ClearLower(&bitfield3, 8);
			bits::Ops32::ClearHigher(&bitfield5, 8);

			MH_GDEBUG("{:X}\n", bitfield1);
			MH_GDEBUG("{:X}\n", bitfield2);
			MH_GDEBUG("{:X}\n", bitfield3);
			MH_GDEBUG("{:X}\n", bitfield5);

			bitfield1 = bits::Ops32::GetLowest1(0xFFFFF000);
			bitfield2 = bits::Ops32::GetHighest1(0x00FFFFFF);

			MH_GDEBUG("{:X}\n", bitfield1);
			MH_GDEBUG("{:X}\n", bitfield2);

			core::sizeT bitfield6 = bits::Ops32::Count1(0xFFF);
			MH_GDEBUG("{}\n", bitfield6);

			bitfield1 = bits::Ops32::SetWordRange1((u32)0x0, 8, 8);
			MH_GDEBUG("{:X}\n", bitfield1);

			TestStruct* bitfields = (TestStruct*)malloc(sizeof(TestStruct));
			platform::Zero(bitfields, sizeof(TestStruct));

			bits::Ops32::SetRange1(bitfields, 0, 0);

			MH_GDEBUG("bitfields:\n{:032b}\n{:032b}\n{:032b}\n{:032b}\n", bitfields->field0, bitfields->field1, bitfields->field2, bitfields->field3);

			bits::Ops32::SetRange0(bitfields, 20, 60);
			
			MH_GDEBUG("bitfields:\n{:032b}\n{:032b}\n{:032b}\n{:032b}\n", bitfields->field0, bitfields->field1, bitfields->field2, bitfields->field3);

			free(bitfields);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {

	}


};
