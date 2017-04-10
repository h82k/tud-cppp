/**
 * Authors: Rick Vogel, Philipp Thomasberger
 * Created: 24.09.2015
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO.Ports;
using System.IO;

namespace Serial
{
    public partial class Form1 : Form
    {
        // buffer for draw/erase message
        // buffer[0] = transfermode
        // buffer[1] = x-coordinate
        // buffer[2] = y-coordinate
        // buffer[3] = on/off
        private byte[] buffer = new byte[4];

        // transfer type - transfer (x,y,on/off) tuples
        private const char transferModeA = (char)0xAA;

        public Form1()
        {
            InitializeComponent();
            // event handler for draw events    
            remoteDisplay1.MouseTrackAddEvent += RemoteDisplay1_MouseTrackAddEvent; ;
            // event handler for erase events
            remoteDisplay1.MouseTrackDeleteEvent += RemoteDisplay1_MouseTrackDeleteEvent;
        }

        private void SendSerial(int x, int y, bool on)
        {
            try
            {
                // note: custom control is scaled 10 times larger than display on board
                //       hence we have to divide the x,y coordinates by 10.
                x = x / 10;
                y = y / 10;

                buffer[0] = 0xAA;
                buffer[1] = (byte)x;
                buffer[2] = (byte)y;
                buffer[3] = (byte)((on) ? 1 : 0);

                serialPort1.Write(buffer, 0, 4);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.ToString());
            }
        }

        private void RemoteDisplay1_MouseTrackDeleteEvent(object sender, MouseTrackDeleteEventArgs e)
        {
            // send erase event
            SendSerial(e.Location.X, e.Location.Y, false);
        }

        private void RemoteDisplay1_MouseTrackAddEvent(object sender, MouseTrackAddEventArgs e)
        {
            // send draw event
            SendSerial(e.Location.X, e.Location.Y, true);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // open form for COM port selection
            ComboBox comboBox = new ComboBox();
            comboBox.Items.AddRange(SerialPort.GetPortNames());
            if(comboBox.Items.Count>0)
            {
                comboBox.SelectedIndex = 0;
            }
            comboBox.Width = 200;

            Form form = new Form();
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Text = "Select COM";
            form.MaximizeBox = false;
            form.FormBorderStyle = FormBorderStyle.FixedDialog;

            form.Controls.Add(comboBox);
            form.Size = comboBox.Size;
            form.AutoSize = true;
            form.ShowDialog();

            // define COM port and open serial connection
            try
            {
                serialPort1.PortName = comboBox.SelectedItem.ToString();
                serialPort1.Open();                
            }           
            // TODO: check source of this exception
            catch (IOException excIO)
            {
                Debug.WriteLine(excIO.ToString());
            }
            // if connection fails close form
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString());
                Close();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort1.Close();
        }
    }
}
