﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Text;

namespace VMLib {
    public class Component : INotifyPropertyChanged {
        static int ComponentIDCounter = 0;
        public int ComponentID { get; }

        public List<MicrocodeCommand> Commands { get; } = new List<MicrocodeCommand>();

        public Component(VMCore core) {
            core.Add(this);
            ComponentID = ComponentIDCounter++;
        }

        public void OnPropertyChanged([CallerMemberName] string prop = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }
        public event PropertyChangedEventHandler PropertyChanged;
    }
}
