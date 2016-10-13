using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing;

namespace Potenciostate
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            refresh();

            CheckForIllegalCrossThreadCalls = false;
            serialPort1.DataReceived += SerialPort1_DataReceived;
        }

        private void SerialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                txtStream.AppendText(serialPort1.ReadExisting());
            }
        }

        private void btn_conn_Click(object sender, EventArgs e)
        {
            try
            {
                if (btn_conn.Text == "Connect")
                {
                    if (serialPort1.IsOpen)
                        serialPort1.Close();
                    serialPort1.PortName = cbPorts.SelectedItem.ToString();
                    serialPort1.Open();
                    btn_conn.BackColor = Color.Red;
                    timer1.Start();
                    btn_conn.Text = "Disconnect";
                }
                else
                {
                    if (serialPort1.IsOpen)
                        serialPort1.Close();
                    btn_conn.BackColor = Color.Green;
                    timer1.Stop();
                    btn_conn.Text = "Connect";
                }

            }
            catch (Exception ex)
            {
                if (serialPort1.IsOpen)
                    serialPort1.Close();
                btn_conn.BackColor = Color.Green;
                timer1.Stop();
                btn_conn.Text = "Connect";
            }
        }
        void refresh()
        {
            var s = SerialPort.GetPortNames();
            cbPorts.Items.Clear();
            foreach (String port in s)
            {
                cbPorts.Items.Add(port);
                cbPorts.SelectedIndex = 0;
            }
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            refresh();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {

            }
        }
    }
}
