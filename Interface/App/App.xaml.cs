﻿using System.Windows;

namespace Interface {
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application {
        private void Application_Startup(object sender, StartupEventArgs e) {
            var win = new Views.MicrocodeProcess {
                Title = "Starfish Virtual Machine"
            };
            win.Show();
        }
    }
}
