namespace Projet5e_PosteDeComande
{
    partial class Poste_De_Controle
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Poste_De_Controle));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.ConnexionSerie_Panel = new System.Windows.Forms.Panel();
            this.VehiculeParcours_Panel = new System.Windows.Forms.Panel();
            this.VehiculeParcours_Label = new System.Windows.Forms.Label();
            this.ConnexionSerie_Label = new System.Windows.Forms.Label();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.Controle_Panel = new System.Windows.Forms.Panel();
            this.Chargement_Panel = new System.Windows.Forms.Panel();
            this.Controle_Label = new System.Windows.Forms.Label();
            this.Chargement_Label = new System.Windows.Forms.Label();
            this.SystemOverview_Panel = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.ConnexionSerie_Panel.SuspendLayout();
            this.VehiculeParcours_Panel.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.Controle_Panel.SuspendLayout();
            this.Chargement_Panel.SuspendLayout();
            this.SystemOverview_Panel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Controls.Add(this.ConnexionSerie_Panel, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.VehiculeParcours_Panel, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 36.19345F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 63.80655F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(800, 660);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // ConnexionSerie_Panel
            // 
            this.ConnexionSerie_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ConnexionSerie_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ConnexionSerie_Panel.Controls.Add(this.ConnexionSerie_Label);
            this.ConnexionSerie_Panel.Location = new System.Drawing.Point(4, 4);
            this.ConnexionSerie_Panel.Margin = new System.Windows.Forms.Padding(4, 4, 2, 2);
            this.ConnexionSerie_Panel.Name = "ConnexionSerie_Panel";
            this.ConnexionSerie_Panel.Size = new System.Drawing.Size(394, 152);
            this.ConnexionSerie_Panel.TabIndex = 0;
            // 
            // VehiculeParcours_Panel
            // 
            this.VehiculeParcours_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.VehiculeParcours_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tableLayoutPanel1.SetColumnSpan(this.VehiculeParcours_Panel, 2);
            this.VehiculeParcours_Panel.Controls.Add(this.SystemOverview_Panel);
            this.VehiculeParcours_Panel.Controls.Add(this.VehiculeParcours_Label);
            this.VehiculeParcours_Panel.Location = new System.Drawing.Point(4, 240);
            this.VehiculeParcours_Panel.Margin = new System.Windows.Forms.Padding(4, 2, 4, 4);
            this.VehiculeParcours_Panel.Name = "VehiculeParcours_Panel";
            this.VehiculeParcours_Panel.Size = new System.Drawing.Size(792, 416);
            this.VehiculeParcours_Panel.TabIndex = 2;
            // 
            // VehiculeParcours_Label
            // 
            this.VehiculeParcours_Label.AutoSize = true;
            this.VehiculeParcours_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.VehiculeParcours_Label.Location = new System.Drawing.Point(3, 0);
            this.VehiculeParcours_Label.Name = "VehiculeParcours_Label";
            this.VehiculeParcours_Label.Size = new System.Drawing.Size(195, 18);
            this.VehiculeParcours_Label.TabIndex = 0;
            this.VehiculeParcours_Label.Text = "Usine - Véhicule et Parcours";
            // 
            // ConnexionSerie_Label
            // 
            this.ConnexionSerie_Label.AutoSize = true;
            this.ConnexionSerie_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConnexionSerie_Label.Location = new System.Drawing.Point(3, 3);
            this.ConnexionSerie_Label.Name = "ConnexionSerie_Label";
            this.ConnexionSerie_Label.Size = new System.Drawing.Size(117, 18);
            this.ConnexionSerie_Label.TabIndex = 1;
            this.ConnexionSerie_Label.Text = "Connexion Serie";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.Controle_Panel, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.Chargement_Panel, 1, 0);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(400, 0);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(400, 238);
            this.tableLayoutPanel2.TabIndex = 3;
            // 
            // Controle_Panel
            // 
            this.Controle_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Controle_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controle_Panel.Controls.Add(this.Controle_Label);
            this.Controle_Panel.Location = new System.Drawing.Point(2, 4);
            this.Controle_Panel.Margin = new System.Windows.Forms.Padding(2, 4, 2, 2);
            this.Controle_Panel.Name = "Controle_Panel";
            this.Controle_Panel.Size = new System.Drawing.Size(196, 232);
            this.Controle_Panel.TabIndex = 0;
            // 
            // Chargement_Panel
            // 
            this.Chargement_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Chargement_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Chargement_Panel.Controls.Add(this.Chargement_Label);
            this.Chargement_Panel.Location = new System.Drawing.Point(202, 4);
            this.Chargement_Panel.Margin = new System.Windows.Forms.Padding(2, 4, 4, 2);
            this.Chargement_Panel.Name = "Chargement_Panel";
            this.Chargement_Panel.Size = new System.Drawing.Size(194, 232);
            this.Chargement_Panel.TabIndex = 1;
            // 
            // Controle_Label
            // 
            this.Controle_Label.AutoSize = true;
            this.Controle_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Controle_Label.Location = new System.Drawing.Point(3, 3);
            this.Controle_Label.Name = "Controle_Label";
            this.Controle_Label.Size = new System.Drawing.Size(130, 18);
            this.Controle_Label.TabIndex = 2;
            this.Controle_Label.Text = "Contrôle de l\'usine";
            // 
            // Chargement_Label
            // 
            this.Chargement_Label.AutoSize = true;
            this.Chargement_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Chargement_Label.Location = new System.Drawing.Point(3, 3);
            this.Chargement_Label.Name = "Chargement_Label";
            this.Chargement_Label.Size = new System.Drawing.Size(166, 18);
            this.Chargement_Label.TabIndex = 3;
            this.Chargement_Label.Text = "Chargement du véhicule";
            // 
            // SystemOverview_Panel
            // 
            this.SystemOverview_Panel.BackgroundImage = global::Projet5e_PosteDeComande.Properties.Resources.Apercu_Systeme_Sans_VehiculeResized;
            this.SystemOverview_Panel.Controls.Add(this.pictureBox1);
            this.SystemOverview_Panel.Location = new System.Drawing.Point(-1, 35);
            this.SystemOverview_Panel.Margin = new System.Windows.Forms.Padding(0);
            this.SystemOverview_Panel.Name = "SystemOverview_Panel";
            this.SystemOverview_Panel.Size = new System.Drawing.Size(792, 374);
            this.SystemOverview_Panel.TabIndex = 1;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.pictureBox1.Image = global::Projet5e_PosteDeComande.Properties.Resources.LeVehiculeEnQuestion_Resized;
            this.pictureBox1.Location = new System.Drawing.Point(200, 168);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(73, 98);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // Poste_De_Controle
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(800, 660);
            this.Controls.Add(this.tableLayoutPanel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Poste_De_Controle";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Poste de controle";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ConnexionSerie_Panel.ResumeLayout(false);
            this.ConnexionSerie_Panel.PerformLayout();
            this.VehiculeParcours_Panel.ResumeLayout(false);
            this.VehiculeParcours_Panel.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.Controle_Panel.ResumeLayout(false);
            this.Controle_Panel.PerformLayout();
            this.Chargement_Panel.ResumeLayout(false);
            this.Chargement_Panel.PerformLayout();
            this.SystemOverview_Panel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel ConnexionSerie_Panel;
        private System.Windows.Forms.Panel VehiculeParcours_Panel;
        private System.Windows.Forms.Label VehiculeParcours_Label;
        private System.Windows.Forms.Label ConnexionSerie_Label;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Panel Controle_Panel;
        private System.Windows.Forms.Panel Chargement_Panel;
        private System.Windows.Forms.Label Controle_Label;
        private System.Windows.Forms.Label Chargement_Label;
        private System.Windows.Forms.Panel SystemOverview_Panel;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

