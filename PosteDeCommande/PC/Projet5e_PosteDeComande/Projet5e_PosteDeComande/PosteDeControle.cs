using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Projet5e_PosteDeComande
{
    public partial class Poste_De_Controle : Form
    {
        char[] cTrameOut;
        char[] cTrameIn;
        public enum StationState
        {
            WEIGHING_STATION = 0,
            OTW_TO_WEIGHING = 1,
            OTW_TO_SORTING = 2,
            SORTING_STATION = 3
        }
        StationState currentState = StationState.WEIGHING_STATION;
        float fPoidsRondelle;
        bool bTrameAEnvoyer;

        public Poste_De_Controle()
        {
            InitializeComponent();
            PopulateCOMPorts();
        }

        private void PopulateCOMPorts()
        {
            //COMPorts_comboBox.Items.AddRange(SerialPort.GetPortNames());
            //if (COMPorts_comboBox.Items.Count > 0)
            //{
            //    COMPorts_comboBox.SelectedIndex = 0; // Select the first port by default
            //}
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //AJOUTER APPEL A CETTE FONCTION QUAND ON RECOIT DES INFOS SUR LA POSITION DU VEHICULE DE LA PART DU BBB
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AjustementPositionVehicule()
        {
            switch (currentState)
            {
                case StationState.WEIGHING_STATION:
                    // Set position for WEIGHING_STATION
                    Vehicle_Picture.Location = new Point(208, 164);
                    Vehicle_Picture.RightToLeft = RightToLeft.No;
                    break;

                case StationState.OTW_TO_WEIGHING:
                    // Set position for OTW_TO_WEIGHING
                    Vehicle_Picture.Location = new Point(356, 174);
                    Vehicle_Picture.RightToLeft = RightToLeft.No;
                    break;

                case StationState.OTW_TO_SORTING:
                    // Set position for OTW_TO_SORTING
                    Vehicle_Picture.Location = new Point(356, 174);
                    Vehicle_Picture.RightToLeft = RightToLeft.Yes;
                    break;

                case StationState.SORTING_STATION:
                    // Set position for SORTING_STATION
                    Vehicle_Picture.Location = new Point(521, 163);
                    Vehicle_Picture.RightToLeft = RightToLeft.Yes;
                    break;
            }
            Vehicle_Picture.Refresh();  //Refreshes the picture's orientation and position after the switch/case
        }
        private void AjustementDuPoids()
        {
            //Poids_TextBox.Text = fPoidsRondelle.ToString();
        }

        private void EnvoiDeLaTrame()
        {
            // Convert the character array (assumed to exist) to a byte array
            //byte[] data = Array.ConvertAll(cTrameOut, c => (byte)c);

            //// Get the selected COM port from a dropdown menu (example: comboBoxCOMPorts)
            //string selectedPort = COMPorts_comboBox.SelectedItem?.ToString();

            //try
            //{
            //    // Open and configure the serial port
            //    using (SerialPort serialPort = new SerialPort(selectedPort, 19200, Parity.None, 8, StopBits.One))
            //    {
            //        serialPort.Open();

            //        // Send the byte array
            //        serialPort.Write(data, 0, data.Length);
            //        MessageBox.Show("Message sent successfully at 19200 baud.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            //    }
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show($"Failed to send message: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //}
        }
        private void ReceptionDeLaTrame()
        {
            
        }
    }
}
