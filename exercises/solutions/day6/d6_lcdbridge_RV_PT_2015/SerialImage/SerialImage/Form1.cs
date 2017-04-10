/**
 * Authors: Rick Vogel, Philipp Thomasberger
 * Created: 24.09.2015
 */

using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Drawing.Imaging;
using System.Diagnostics;

namespace SerialImage
{
    public partial class Form1 : Form
    {                
        // tranfser type - transfer as complete frame buffer
        private const byte transferModeB = 0xBB;
        // selected transfer mode
        private const byte transferMode = transferModeB;              
        // buffer for transfer mode B   Note: +1 for transfermode prefix
        private byte[] bufferTransferModeB = new byte[128 * 8 + 1];

        // tranfser the guven bitmap into the corresponding buffer
        private void transferImageToBuffer_ModeB(Bitmap bitmap)
        {
            int bufferIndex = 0;
            bufferTransferModeB[0] = transferModeB;
            bufferIndex++;
            
            // each column            
            for (int x = 0; x < bitmap.Width; x++)
            {
                // 8 rows in curretn column
                for (int y = 0; y < bitmap.Height; y += 8)
                {                    
                    int value32Bit = 0;
                    // combine 8 columns into value 
                    for (int z = 0; z < 8; z++)
                    {
                        Color pixelOld = bitmap.GetPixel(x, y + z);
                        float grayscale = (pixelOld.R + pixelOld.G + pixelOld.B) / 3;
                        // set white bit
                        if (grayscale < 128)
                        {
                            value32Bit += (int)Math.Pow(2, z);
                        }
                    }                    
                    bufferTransferModeB[bufferIndex] = (byte)value32Bit;
                    bufferIndex++;
                }
            }            
        }

        private void applyBinarization(Bitmap bitmap)
        {
            // apply image thresholding
            for (int y = 0; y < bitmap.Height; y++)
            {
                for (int x = 0; x < bitmap.Width; x++)
                {
                    Color pixelOld = bitmap.GetPixel(x, y);
                    Color pixelNew;

                    // calculate grayscale of current pixel
                    float grayscale = (pixelOld.R + pixelOld.G + pixelOld.B) / 3;

                    if (grayscale > 128)
                        pixelNew = Color.White;
                    else
                        pixelNew = Color.Black;

                    // define current pixel as its grayscale
                    bitmap.SetPixel(x, y, pixelNew);
                }
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            // show file selection dialog
            openFileDialog1.Multiselect = false;
            openFileDialog1.Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";

            // if valid file has been selected
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // load selected file into bitmap object
                Bitmap bitmap = new Bitmap(openFileDialog1.FileName);

                try
                {
                    // apply binarization on bitmap
                    applyBinarization(bitmap);

                    // scale for display on board
                    bitmap = new Bitmap(bitmap, new Size(128, 64));

                    // assign picturebox image
                    pictureBox1.Image = bitmap;                    

                    try
                    {
                        serialPort1.Open();

                        // transfermode A is ineffective
                        if (transferMode == transferModeB)
                        {
                            transferImageToBuffer_ModeB(bitmap);
                            serialPort1.Write(bufferTransferModeB, 0, bufferTransferModeB.Length);
                        }

                        serialPort1.Close();
                    }
                    catch (Exception exc)
                    {
                        MessageBox.Show(exc.ToString());
                    }

                }

                catch (Exception exc)
                {
                    MessageBox.Show(exc.ToString());
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // open form for COM port selection
            ComboBox comboBox = new ComboBox();
            comboBox.Items.AddRange(SerialPort.GetPortNames());
            if (comboBox.Items.Count > 0)
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
    }
}
