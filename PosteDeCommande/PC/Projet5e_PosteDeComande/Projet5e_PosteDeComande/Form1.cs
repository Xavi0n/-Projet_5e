using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Projet5e_PosteDeComande
{
    public partial class Poste_De_Controle : Form
    {
        public enum StationState
        {
            WEIGHING_STATION = 0,
            OTW_TO_WEIGHING = 1,
            OTW_TO_SORTING = 2,
            SORTING_STATION = 3
        }
        StationState currentState = StationState.WEIGHING_STATION;

        public Poste_De_Controle()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }


        private void AjustementPositionVehicule()
        {
            if (currentState == StationState.WEIGHING_STATION)
            { }
            if (currentState == StationState.SORTING_STATION)
            { }
            if (currentState == StationState.OTW_TO_WEIGHING)
            { }
            if (currentState == StationState.OTW_TO_SORTING)
            { }
        }
    }
}
