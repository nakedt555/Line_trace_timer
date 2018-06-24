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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.Windows.Threading;
using System.Windows.Interop;

namespace line_trace_timer
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        DispatcherTimer dispatcherTimer;    // タイマーオブジェクト
        int TimeLimit = 300;                 // 制限時間
        DateTime StartTime;                 // カウント開始時刻
        TimeSpan nowtimespan;               // Startボタンが押されてから現在までの経過時間
        TimeSpan oldtimespan;               // 一時停止ボタンが押されるまでに経過した時間の蓄積
        private processRecivedData ProcessReciveData;
        private Boolean readyFlag = false;
        private Boolean startFlag = false;
        private Boolean restartFlag = false;
        private Boolean stopFlag = true;
        private Boolean goalFlag = false;

        private long num = 0;
        private int measureDisplay = 0;

        public MainWindow()
        {
            InitializeComponent();

            // コンポーネントの状態を初期化　
            lblTime.Content = "00:00:000";
            btnStart.IsEnabled = true;
            btnStop.IsEnabled = false;
            btnReset.IsEnabled = true;

            // タイマーのインスタンスを生成
            dispatcherTimer = new DispatcherTimer(DispatcherPriority.Normal);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1);
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);

            TimerReset();

            connectSerialInterfase();
            ProcessReciveData = new processRecivedData(this);

            debugPrint.Content = "";
        }

        // タイマー Tick処理
        void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            nowtimespan = DateTime.Now.Subtract(StartTime);
            lblTime.Content = oldtimespan.Add(nowtimespan).ToString(@"mm\:ss\:fff");

            setReady.FontSize = 120;
            if(num++ % 20 == 0)
            {
                switch (measureDisplay)
                {
                    case 0:
                        setReady.Content = "｜計測中｜";
                        measureDisplay++;
                        break;
                    case 1:
                        setReady.Content = "＼計測中＼";
                        measureDisplay++;
                        break;
                    case 2:
                        setReady.Content = "―計測中―";
                        measureDisplay++;
                        break;
                    case 3:
                        setReady.Content = "／計測中／";
                        measureDisplay = 0;
                        break;
                }
            }

            if (TimeSpan.Compare(oldtimespan.Add(nowtimespan), new TimeSpan(0, 0, TimeLimit)) >= 0)
            {
                TimerStop();
                TimerReset();
                //MessageBox.Show(String.Format("{0}秒経過しました。", TimeLimit),
                //                "Infomation", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }

        // ボタンクリック時の処理分岐
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Control ctrl = (Control)sender;
            switch (ctrl.Name)
            {
                case "btnStart":
                    TimerStart();
                    break;

                case "btnStop":
                    TimerStop();
                    break;

                case "btnReset":
                    TimerReset();
                    break;

                default:
                    break;
            }
        }

        // タイマー操作：開始
        public void TimerStart()
        {
            if (goalFlag)
            {

            }
            else if (startFlag == false)
            {
                btnStart.IsEnabled = false;
                btnStop.IsEnabled = true;
                btnReset.IsEnabled = false;
                StartTime = DateTime.Now;
                dispatcherTimer.Start();

                resetReadyChar();

                startFlag = true;
            }
            else if (restartFlag == true)
            {
                btnStart.IsEnabled = false;
                btnStop.IsEnabled = true;
                btnReset.IsEnabled = false;
                StartTime = DateTime.Now;
                dispatcherTimer.Start();

                restartFlag = false;
            }
        }

        // タイマー操作：停止
        void TimerStop()
        {
            btnStart.IsEnabled = true;
            btnStop.IsEnabled = false;
            btnReset.IsEnabled = true;
            oldtimespan = oldtimespan.Add(nowtimespan);
            dispatcherTimer.Stop();

            if(startFlag == true)
            {
                restartFlag = true;
            }

            stopFlag = true;
        }

        // タイマー操作：リセット
        void TimerReset()
        {
            if (stopFlag == true)
            {
                oldtimespan = new TimeSpan();
                lblTime.Content = "00:00:000";
                resetReadyChar();
            }
            if(serialOpenFlag == true)
            {
                byte[] sendData = { 0x10 };

                serialPort.Write(sendData, 0, 1);
                debugPrint.Content = "Send OK!";
            }
        }

        //マイコンからの信号があった場合、READYを表示
        public void setStartTimer()
        {
            if(readyFlag == false && startFlag == false) {
                setReadyChar();
                readyFlag = true;
                stopFlag = false;
            }
        }

        public void setStopTimer()
        {
            TimerStop();
            setReady.FontSize = 180;
            setReady.Content = "GOAL!";
            lblTime.Foreground = new SolidColorBrush(Colors.Red);

            restartFlag = false;
            startFlag = true;
            goalFlag = true;
        }

        public void setReadyChar()
        {
            if (readyFlag == false)
            {
                setReady.FontSize = 180;
                setReady.Content = "READY!";
            }
        }

        void resetReadyChar()
        {
            setReady.FontSize = 180;
            setReady.Content = "";
            lblTime.Foreground = new SolidColorBrush(Colors.Black);

            readyFlag = false;
            startFlag = false;
            goalFlag = false;
        }

        private void Window_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.S)
            {
                setStartTimer();
            }

            if (e.Key == Key.D)
            {
                TimerStart();
            }

            if (e.Key == Key.F)
            {
                TimerStop();
            }

            if (e.Key == Key.G)
            {
                setStopTimer();
            }

            if (e.Key == Key.R)
            {
                TimerReset();
            }

            if(e.Key == Key.Escape)
            {
                TimerStop();
                TimerReset();
            }
        }

        public System.IO.Ports.SerialPort serialPort;
        public bool serialInitializeFlag = false;
        public bool serialOpenFlag = false;

        void connectSerialInterfase()
        {
            if (serialInitializeFlag == false)
            {
                serialInitializeFlag = true;
            }
            else
            {
                //setDebugPrint("[ INFO ] COM PORT ( " + serialPort.PortName + " ) を切断します．");
                serialOpenFlag = false;
                serialPort.Close();
            }
            var selectSerialWindow = new selectSerialPort();
            selectSerialWindow.MainWindowPointer = this;
            selectSerialWindow.Show();

            //取り敢えずCOM18に設定
            serialPort = new System.IO.Ports.SerialPort("COM18", 9600, System.IO.Ports.Parity.None, 8, System.IO.Ports.StopBits.One);
            serialPort.NewLine = Environment.NewLine;
            serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(serialPort_DataReceivedHandler);
        }

        public bool openSerialPort(string portName, int baudRate)
        {
            if (portName != System.String.Empty)
            {
                serialPort.PortName = portName;
                serialPort.BaudRate = baudRate;
                try
                {
                    serialPort.Open();

                    if (serialPort.IsOpen)
                    {
                        //textBoxDebug.Text = serialPort.PortName + "をOpenしました．";
                        //setDebugPrint("[ INFO ] COM PORT ( " + serialPort.PortName + " ) を開きました．");
                        serialOpenFlag = true;

                        return true;
                    }

                    return true;

                }
                catch
                {
                    //setDebugPrint("[ ERROR ] COM PORT ( " + serialPort.PortName + " ) を開けませんでした．");
                    return false;
                }
            }
            else
            {
                //textBoxDebug.Text = "[ ERROR ] Port nameを設定してください．";
                //setDebugPrint("[ ERROR ] Wrong port name");
                return true;
            }
        }

        private void serialPort_DataReceivedHandler(object sender,
            System.IO.Ports.SerialDataReceivedEventArgs e)
        {

            try
            {
                textBoxDebug.Dispatcher.Invoke(
                    new Action(() =>
                    {
                        string str = serialPort.ReadExisting();
                        //setDebugPrint(str);

                        foreach (byte c in str)
                        {
                            //setDebugPrint(c.ToString()); //debug
                            ProcessReciveData.inputData(c);
                        }
                    })
                );//beginInbokeだと呼び出し直後に元のコントロールに制御が戻る
            }
            catch
            {
                textBoxDebug.Dispatcher.Invoke(
                    new Action(() =>
                    {
                        //setDebugPrint("[ ERROR ] COM PORT ( " + serialPort.PortName + " ) と通信できませんでした．");
                    })
                );
            }
        }
    }

    class processRecivedData

    {
        private MainWindow MainWindowPointer;
        private int num = 0;

        public processRecivedData(MainWindow mainWindowPointer)
        {
            MainWindowPointer = mainWindowPointer;
        }

        public void inputData(byte data)
        {
            switch (data)
            {
                case 0x01:
                    num++;
                    switch (num % 3)
                    {
                        case 0:
                            MainWindowPointer.debugPrint.Content = "通信中.  ";
                            break;
                        case 1:
                            MainWindowPointer.debugPrint.Content = "通信中.. ";
                            break;
                        case 2:
                            MainWindowPointer.debugPrint.Content = "通信中...";
                            break;
                    }

                    break;

                case 0x02:
                    MainWindowPointer.setStartTimer();
                    break;

                case 0x03:
                    MainWindowPointer.TimerStart();
                    break;

                case 0x04:
                    MainWindowPointer.setStopTimer();
                    break;
            }
        }

    }
}
