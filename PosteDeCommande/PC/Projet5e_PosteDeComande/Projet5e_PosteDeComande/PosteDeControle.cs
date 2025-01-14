﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
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
        private SerialPort uartPort;
        byte[] cTrameOut = new byte[11] {0x24,0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        byte[] cTrameIn  = new byte[11] {0x24,0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        private string callingFunction = string.Empty;
        string selectedPort;

        public enum StationState
        {
            WEIGHING_STATION,
            OTW_TO_WEIGHING,
            OTW_TO_SORTING,
            SORTING_STATION
        }
        StationState currentState = StationState.WEIGHING_STATION;
        double dPoidsRondelle;

        public Poste_De_Controle()
        {
            InitializeComponent();
            PopulateCOMPorts();
            uartPort = new SerialPort();
            this.FormClosing += new FormClosingEventHandler(MainForm_FormClosing);
            uartPort.DataReceived += ReceptionDeLaTrame;            // Register the DataReceived event handler
            Grams_Checkbox.Checked = true;

        }

        private void PopulateCOMPorts()
        {
            COMPorts_comboBox.Items.AddRange(SerialPort.GetPortNames());
            if (COMPorts_comboBox.Items.Count > 0)
            {
                COMPorts_comboBox.SelectedIndex = 0; // Select the first port by default
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void AjustementPositionVehicule()
        {
           switch (cTrameIn[7])             // Convertir 1, 3 ou 5 selon la position envoyée par le véhicule
            {                               // en l'une des 4 positions posibles pour l'affichage du véhicule
                case 1:
                    currentState = StationState.WEIGHING_STATION;
                    break;
                case 3:
                    if (currentState == StationState.WEIGHING_STATION)
                    {
                        currentState = StationState.OTW_TO_SORTING;
                    }
                    else if (currentState == StationState.SORTING_STATION)
                    {
                        currentState = StationState.OTW_TO_WEIGHING;
                    }
                    break;
                case 5:
                    currentState = StationState.SORTING_STATION;
                    break;
            }
            switch (currentState)           // Actualisation de la position du véhicule
            {
                case StationState.WEIGHING_STATION:
                    // Set position for WEIGHING_STATION
                    Vehicle_Picture.Location = new Point(208, 164);
                    if (Vehicle_Picture.IsMirrored == true)
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                        Vehicle_Picture.Refresh();
                    }
                    else
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipNone);
                        Vehicle_Picture.Refresh();
                    }
                    break;

                case StationState.OTW_TO_WEIGHING:
                    // Set position for OTW_TO_WEIGHING
                    Vehicle_Picture.Location = new Point(356, 174);
                    if (Vehicle_Picture.IsMirrored == true)
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                        Vehicle_Picture.Refresh();
                    }
                    else
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipNone);
                        Vehicle_Picture.Refresh();
                    }
                    break;

                case StationState.OTW_TO_SORTING:
                    // Set position for OTW_TO_SORTING
                    Vehicle_Picture.Location = new Point(356, 174);
                    if (Vehicle_Picture.IsMirrored == false)
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                        Vehicle_Picture.Refresh();
                    }
                    else
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipNone);
                        Vehicle_Picture.Refresh();
                    }
                    break;

                case StationState.SORTING_STATION:
                    // Set position for SORTING_STATION
                    Vehicle_Picture.Location = new Point(521, 163);
                    if (Vehicle_Picture.IsMirrored == false)
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                        Vehicle_Picture.Refresh();
                    }
                    else
                    {
                        Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipNone);
                        Vehicle_Picture.Refresh();
                    }
                    break;
            }
        }
        private void AjustementDuPoids()
        {
            double dGramsToOunces = 28.3495;            //Valeur de conversion grammes / onces

            dPoidsRondelle = Convert.ToDouble(cTrameIn[5]);
            dPoidsRondelle = dPoidsRondelle + Convert.ToDouble(((cTrameIn[6])/100));

            if (Ounces_Checkbox.Checked == true)        //Convertir le poids de grammes a onces si 
            {                                           //la case onces est cochée sur l'interface
                dPoidsRondelle = dPoidsRondelle / dGramsToOunces;
            }
            AffichagePoids_Label.Text = dPoidsRondelle.ToString();  //Afficher le poids de la rondelle sur l'interface
        }
        private void AjustementDeLaCouleur()
        {
            if (cTrameIn[4] == 'O')
            {
                OrangePuck_Panel.Visible = true;
                BlackPuck_Panel.Visible  = false;
                GreyPuck_Panel.Visible   = false;
                CouleurNonDefinie_Label.Visible  = false;
            }
            else if (cTrameIn[4] == 'N')
            {
                OrangePuck_Panel.Visible = false;
                BlackPuck_Panel.Visible  = true;
                GreyPuck_Panel.Visible   = false;
                CouleurNonDefinie_Label.Visible  = false;
            }
            else if (cTrameIn[4] == 'M')
            {
                OrangePuck_Panel.Visible = false;
                BlackPuck_Panel.Visible  = false;
                GreyPuck_Panel.Visible   = true;
                CouleurNonDefinie_Label.Visible  = false;
            }
        }
        private void EnvoiDeLaTrame()
        {
            // Disable the DataReceived event temporarily to avoid conflicts on UART
            uartPort.DataReceived -= ReceptionDeLaTrame;
            // Prepare the data frame based on the command
            if (callingFunction == "Demarrer")
            {
                cTrameOut[0] = 0x24;    // Start condition for UART frames
                cTrameOut[1] = 0x08;    // Amount of bytes to be transmitted
                cTrameOut[2] = 0x01;    // Identifier for Control post
                cTrameOut[3] = 0x44;    // Command ('D' for start)     
            }
            else if (callingFunction == "Arreter")
            {
                cTrameOut[0] = 0x24;    // Start condition for UART frames
                cTrameOut[1] = 0x08;    // Amount of bytes to be transmitted
                cTrameOut[2] = 0x01;    // Identifier for Control post
                cTrameOut[3] = 0x41;    // Command ('A' for stop) 
            }
            else if (callingFunction == "Connecter")
            {
                cTrameOut[0] = 0x24;    // Start condition for UART frames
                cTrameOut[1] = 0x08;    // Amount of bytes to be transmitted
                cTrameOut[2] = 0x01;    // Identifier for Control post
                cTrameOut[3] = 0x52;    // Command ('R' for reset) 
            }
            byte checksum = 0x00;
            for (int i = 2; i < 10; i++)        // Calculate checksum
            {
                checksum += cTrameOut[i];
            }
            cTrameOut[10] = checksum;           // Store checksum

            // Send the data frame over UART
            Debug.WriteLine("Trame envoyée au Beagle via UART:");
            foreach (byte b in cTrameOut)
            {
                Debug.Write($"{b:x2} ");                    // Debugging output
                uartPort.Write(new byte[] { b }, 0, 1);     // Send byte by byte
            }
            Debug.WriteLine("\n");
            Array.Clear(cTrameOut, 0, cTrameOut.Length);    // Clear frame data after sending
            uartPort.DataReceived += ReceptionDeLaTrame;    // Re-enable the DataReceived event after the data is sent
        }

        private delegate void DelegateReceiveManagement();
        private void ReceptionDeLaTrame(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                if (uartPort.BytesToRead >= 11)          // Only process data when available
                {
                    Array.Clear(cTrameIn, 0, cTrameIn.Length);      //Clear frame data before attempting to read
                    uartPort.Read(cTrameIn, 0, cTrameIn.Length);    // Read up to 11 bytes from the serial port

                    Debug.WriteLine("Trame Reçue par le PC: ");
                    foreach (byte b in cTrameIn)
                    {
                        Debug.Write($"{b:x2} ");
                    }
                    Debug.WriteLine("\n");

                    if (cTrameIn[0] == 0x24)                    // Check if the first byte is '$' (0x24 in ASCII)
                    {
                        byte checksum = 0;
                        for (int i = 2; i < 10; i++)            // Sum all bytes except checksum byte
                        {
                            checksum += cTrameIn[i];
                        }

                        if (checksum == cTrameIn[10])           //If the checksum matches, update the inteface
                        {
                            Invoke(new DelegateReceiveManagement(ReceiveManagement));
                        }
                        else   //Handle checksum mismatch
                        {
                            MessageBox.Show("Checksum mismatch.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else   //Handles invalid start byte
                    {
                        MessageBox.Show("Incorrect frame start byte. Expected '$'.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    uartPort.DiscardInBuffer();     //Clears the UART port data buffer after it has been handled
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error receiving data: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        void ReceiveManagement()
        {
            if (cTrameIn[3] == 'I')             //Si la trame donne une information au système
            {
                AjustementDuPoids();            //Ajustement du poids de la puck transportée par le véhicule
                AjustementDeLaCouleur();        //Ajustement de la couleur de la puck transportée par le véhicule
                AjustementPositionVehicule();   //Ajustement de la position du véhicule
            }
            else if (cTrameIn[3] == 'D')
            {
                Arreter_Button.Enabled = true;          //Activation du bouton pour arreter l'usine
                Connecter_Button.Enabled = false;       //Desactivation de l'option de deconnecter le port UART
                Demarrer_Button.Enabled = false;        //Desactivation du bouton Demarrer
            }
            else if (cTrameIn[3] == 'A')
            {
                Demarrer_Button.Enabled = true;         //Activation du bouton pour demarrer l'usine
                Connecter_Button.Enabled = true;        //Reactivation de l'option de deconnecter le port UART
                Arreter_Button.Enabled = false;         //Desactivation du bouton Demarrer
            }
            else if (cTrameIn[3] == 'K')
            {
                Demarrer_Button.Enabled = true;                 //Activation du bouton pour demarrer l'usine
                Connecter_Button.Enabled = false;               //Reactivation de l'option de deconnecter le port UART
                Arreter_Button.Enabled = false;                 //Desactivation du bouton Demarrer
                AffichagePoids_Label.Text = "Non défini";       //Reset du label du poids sur un reset de l'usine
                OrangePuck_Panel.Visible = false;               //Reset de l'affichage de la couleur
                BlackPuck_Panel.Visible = false;                //^^^^^^
                GreyPuck_Panel.Visible = false;                 //^^^^^^
                CouleurNonDefinie_Label.Visible = false;        //^^^^^^
                Vehicle_Picture.Location = new Point(208, 164);
                if (Vehicle_Picture.IsMirrored == true)
                {
                    Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                }
                else
                {
                    Vehicle_Picture.Image.RotateFlip(RotateFlipType.RotateNoneFlipNone);
                }
            }
        }
        private void Connecter_Button_Click(object sender, EventArgs e)
        {
            if (Connecter_Button.Text == "Connecter")           //Si l'utilisateur désire se connecter
            {                                                   //
                Demarrer_Button.Enabled = true;                 //On active l'option pour démarrer l'usine
                COMPorts_comboBox.Enabled = false;              //On désactive l'option de changer de COM port
                Connecter_Button.Text = "Déconnecter";          //On remplace le texte du bouton par "Déconnecter"
                InitUART();
                callingFunction = "Connecter";
                EnvoiDeLaTrame();
            }
            else if (Connecter_Button.Text == "Déconnecter")    //Si l'utilisateur désire se déconnecter
            {                                                   //
                Connecter_Button.Text = "Connecter";            //On remplace le texte du bouton par "Connecter"
                Demarrer_Button.Enabled = false;                //On désactive l'option pour démarrer l'usine
                COMPorts_comboBox.Enabled = true;               //On réactive l'option de changer de COM port
                CloseUART();
            }
        }
        private void Demarrer_Button_Click(object sender, EventArgs e)
        {
            Arreter_Button.Enabled = true;          //Activation du bouton pour arreter l'usine
            Connecter_Button.Enabled = false;       //Desactivation de l'option de deconnecter le port UART
            callingFunction = "Demarrer";           //Garde le nom de la fonction qui a appelé l'envoi de la trame
            EnvoiDeLaTrame();
            Demarrer_Button.Enabled = false;        //Desactivation du bouton Demarrer
        }
        private void Arreter_Button_Click(object sender, EventArgs e)
        {
            Demarrer_Button.Enabled = true;         //Activation du bouton pour demarrer l'usine
            Connecter_Button.Enabled = true;        //Reactivation de l'option de deconnecter le port UART
            callingFunction = "Arreter";            //Garde le nom de la fonction qui a appelé l'envoi de la trame
            EnvoiDeLaTrame();
            Arreter_Button.Enabled = false;         //Desactivation du bouton Demarrer
        }
        private void InitUART()
        {
            selectedPort = COMPorts_comboBox.SelectedItem.ToString();    // Get the selected COM port

            if (uartPort.IsOpen)    {uartPort.Close();}    // Close the port if it's already open

            try           // Configure the serial port
            {
                uartPort.PortName = selectedPort;       //Use the port selected in the drop down box
                uartPort.BaudRate = 19200;              //Set baud rate to 19200
                uartPort.Parity = Parity.None;          //No parity bit
                uartPort.StopBits = StopBits.One;       //One stop bit
                uartPort.DataBits = 8;                  //8 bit structure
                uartPort.Handshake = Handshake.None;    //No handshake
                
                uartPort.Open();                        //Open the port
                uartPort.DiscardInBuffer();             //Clear UART buffer
                MessageBox.Show($"Successfully opened {selectedPort}!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to open {selectedPort}: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void CloseUART()
        {
            if (uartPort.IsOpen)
            {
                try
                {
                    uartPort.Close();
                    MessageBox.Show($"Successfully closed {selectedPort}!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Failed to close {selectedPort}: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        private void Ounces_Checkbox_Click(object sender, EventArgs e)
        {
            Ounces_Checkbox.Checked = true;
            Grams_Checkbox.Checked = false;
        }
        private void Grams_Checkbox_Click(object sender, EventArgs e)
        {
            Grams_Checkbox.Checked = true;
            Ounces_Checkbox.Checked= false;
        }
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (uartPort.IsOpen)
            {
                uartPort.Close();
            }
        }
    }
}
