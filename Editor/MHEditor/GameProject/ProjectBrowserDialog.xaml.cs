using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace MHEditor.GameProject
{
    /// <summary>
    /// Logique d'interaction pour ProjectBrowserDialog.xaml
    /// </summary>
    public partial class ProjectBrowserDialog : Window
    {
        public ProjectBrowserDialog()
        {
            InitializeComponent();
        }

        private void openCreateProject_Click(object sender, RoutedEventArgs e)
        {
            if (sender == btnOpenProject)
            {
                if (btnCreateProject.IsChecked == true)
                {
                    btnCreateProject.IsChecked = false;
                    browserContent.Margin = new Thickness(0);
                }
                btnOpenProject.IsChecked = true;
            }
            else
            {
                if (btnOpenProject.IsChecked == true)
                {
                    btnOpenProject.IsChecked = false;
                    browserContent.Margin = new Thickness(-800, 0, 0, 0);
                }
                btnCreateProject.IsChecked = true;
            }
        }
    }
}
