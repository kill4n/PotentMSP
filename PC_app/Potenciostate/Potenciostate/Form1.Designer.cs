namespace Potenciostate
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.cbPorts = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.btn_conn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txtStream = new System.Windows.Forms.TextBox();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // cbPorts
            // 
            this.cbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPorts.FormattingEnabled = true;
            this.cbPorts.Location = new System.Drawing.Point(16, 29);
            this.cbPorts.Name = "cbPorts";
            this.cbPorts.Size = new System.Drawing.Size(189, 24);
            this.cbPorts.TabIndex = 0;
            // 
            // btn_conn
            // 
            this.btn_conn.BackColor = System.Drawing.Color.Green;
            this.btn_conn.Location = new System.Drawing.Point(211, 23);
            this.btn_conn.Name = "btn_conn";
            this.btn_conn.Size = new System.Drawing.Size(108, 34);
            this.btn_conn.TabIndex = 1;
            this.btn_conn.Text = "Connect";
            this.btn_conn.UseVisualStyleBackColor = false;
            this.btn_conn.Click += new System.EventHandler(this.btn_conn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 69);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(87, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Data Stream";
            // 
            // txtStream
            // 
            this.txtStream.Location = new System.Drawing.Point(15, 103);
            this.txtStream.Multiline = true;
            this.txtStream.Name = "txtStream";
            this.txtStream.Size = new System.Drawing.Size(417, 182);
            this.txtStream.TabIndex = 3;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(325, 22);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(108, 34);
            this.btnRefresh.TabIndex = 4;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(444, 304);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.txtStream);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_conn);
            this.Controls.Add(this.cbPorts);
            this.Name = "Form1";
            this.Text = "Potenciostato";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbPorts;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button btn_conn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtStream;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Timer timer1;
    }
}

