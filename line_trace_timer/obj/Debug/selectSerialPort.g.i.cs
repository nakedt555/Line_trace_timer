﻿#pragma checksum "..\..\selectSerialPort.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "8FC93E14805A150906322BBB63AC321B0A193C64"
//------------------------------------------------------------------------------
// <auto-generated>
//     このコードはツールによって生成されました。
//     ランタイム バージョン:4.0.30319.42000
//
//     このファイルへの変更は、以下の状況下で不正な動作の原因になったり、
//     コードが再生成されるときに損失したりします。
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using line_trace_timer;


namespace line_trace_timer {
    
    
    /// <summary>
    /// selectSerialPort
    /// </summary>
    public partial class selectSerialPort : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 13 "..\..\selectSerialPort.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox SerialComPort;
        
        #line default
        #line hidden
        
        
        #line 15 "..\..\selectSerialPort.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox SerialBaudRate;
        
        #line default
        #line hidden
        
        
        #line 16 "..\..\selectSerialPort.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button SerialStartBtn;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\selectSerialPort.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button SerialCancelBtn;
        
        #line default
        #line hidden
        
        
        #line 18 "..\..\selectSerialPort.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button SerialUpdadteBtn;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/line_trace_timer;component/selectserialport.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\selectSerialPort.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.SerialComPort = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 2:
            this.SerialBaudRate = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 3:
            this.SerialStartBtn = ((System.Windows.Controls.Button)(target));
            
            #line 16 "..\..\selectSerialPort.xaml"
            this.SerialStartBtn.Click += new System.Windows.RoutedEventHandler(this.SerialStartBtn_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.SerialCancelBtn = ((System.Windows.Controls.Button)(target));
            
            #line 17 "..\..\selectSerialPort.xaml"
            this.SerialCancelBtn.Click += new System.Windows.RoutedEventHandler(this.SerialCancelBtn_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.SerialUpdadteBtn = ((System.Windows.Controls.Button)(target));
            
            #line 18 "..\..\selectSerialPort.xaml"
            this.SerialUpdadteBtn.Click += new System.Windows.RoutedEventHandler(this.SerialUpdadteBtn_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

