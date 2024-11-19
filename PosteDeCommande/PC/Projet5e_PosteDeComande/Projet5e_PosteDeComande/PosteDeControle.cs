using System;
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
        char[] cTrameOut;
        char[] cTrameIn;
        string sCouleurBloc = "non_defini";
        private string callingFunction = string.Empty;

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
            COMPorts_comboBox.Items.AddRange(SerialPort.GetPortNames());
            if (COMPorts_comboBox.Items.Count > 0)
            {
                COMPorts_comboBox.SelectedIndex = 0; // Select the first port by default
            }
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
        private void AjustementDeLaCouleur()
        {
            if (sCouleurBloc == "non_defini")
            {
                OrangePuck_Panel.Visible = false;
                BlackPuck_Panel.Visible  = false;
                GreyPuck_Panel.Visible   = false;
                CouleurNonDefinie_Label.Visible  = true;
            }
            if (sCouleurBloc == "orange")
            {
                OrangePuck_Panel.Visible = true;
                BlackPuck_Panel.Visible  = false;
                GreyPuck_Panel.Visible   = false;
                CouleurNonDefinie_Label.Visible  = false;
            }
            if (sCouleurBloc == "noir")
            {
                OrangePuck_Panel.Visible = false;
                BlackPuck_Panel.Visible  = true;
                GreyPuck_Panel.Visible   = false;
                CouleurNonDefinie_Label.Visible  = false;
            }
            if (sCouleurBloc == "gris")
            {
                OrangePuck_Panel.Visible = false;
                BlackPuck_Panel.Visible  = false;
                GreyPuck_Panel.Visible   = true;
                CouleurNonDefinie_Label.Visible  = false;
            }
        }

        private void EnvoiDeLaTrame()
        {
            if (callingFunction == "Demarrer")
            {

            }
            else if (callingFunction == "Arreter")
            {

            }
            else
            {
                Debug.WriteLine("Called from an unknown source");
            }
        }
        private void ReceptionDeLaTrame()
        {
            //Faire ici la reception de la trame, ainsi que le stockage
            //des informations recues dans les variables appropriées
            AjustementDuPoids();
            AjustementDeLaCouleur();
            AjustementPositionVehicule();
        }

        private void Connecter_Button_Click(object sender, EventArgs e)
        {
            if (Connecter_Button.Text == "Connecter")           //Si l'utilisateur désire se connecter
            {                                                   //
                Demarrer_Button.Enabled = true;                 //On active l'option pour démarrer l'usine
                COMPorts_comboBox.Enabled = false;              //On désactive l'option de changer de COM port
                Connecter_Button.Text = "Déconnecter";          //On remplace le texte du bouton par "Déconnecter"
                InitUART();
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
            //Mettre dans la trame ce que l'on veut envoyer
            EnvoiDeLaTrame();
            //Reset de la trame pour la prochaine utilisation
            Demarrer_Button.Enabled = false;        //Desactivation du bouton Demarrer
        }
        private void Arreter_Button_Click(object sender, EventArgs e)
        {
            Demarrer_Button.Enabled = true;         //Activation du bouton pour demarrer l'usine
            Connecter_Button.Enabled = true;        //Reactivation de l'option de deconnecter le port UART
            callingFunction = "Arreter";            //Garde le nom de la fonction qui a appelé l'envoi de la trame
            //Mettre dans la trame ce que l'on veut envoyer
            EnvoiDeLaTrame();
            //Reset de la trame pour la prochaine utilisation
            Arreter_Button.Enabled = false;         //Desactivation du bouton Demarrer
        }

        private void InitUART()
        {
            
        }
        private void CloseUART()
        {

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
    }
}
