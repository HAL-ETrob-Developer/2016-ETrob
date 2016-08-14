namespace EV3RT_2016_FORM
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.createSW = new System.Windows.Forms.Button();
            this.textBoxSpdP = new System.Windows.Forms.TextBox();
            this.textBoxSpdI = new System.Windows.Forms.TextBox();
            this.textBoxSpdD = new System.Windows.Forms.TextBox();
            this.textBoxDegD = new System.Windows.Forms.TextBox();
            this.textBoxDegI = new System.Windows.Forms.TextBox();
            this.textBoxDegP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupSpd = new System.Windows.Forms.GroupBox();
            this.groupDeg = new System.Windows.Forms.GroupBox();
            this.righitStateDataGrid = new System.Windows.Forms.DataGridView();
            this.RIdxNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxNextCond = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.RIdxCoundValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxActNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxNextNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupRighitIndex = new System.Windows.Forms.GroupBox();
            this.RIdxSortSw = new System.Windows.Forms.Button();
            this.groupLeftIndex = new System.Windows.Forms.GroupBox();
            this.LIdxSortSw = new System.Windows.Forms.Button();
            this.leftStateDataGrid = new System.Windows.Forms.DataGridView();
            this.LIdxNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxNextCond = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.LIdxCoundValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxActNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxNextNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.loadSW = new System.Windows.Forms.Button();
            this.ev3OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.groupRunningIndex = new System.Windows.Forms.GroupBox();
            this.runninngIndexGridView = new System.Windows.Forms.DataGridView();
            this.RunNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunTrun = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunTailDeg = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunBalance = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ControlLabel = new System.Windows.Forms.Label();
            this.groupSpd.SuspendLayout();
            this.groupDeg.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.righitStateDataGrid)).BeginInit();
            this.groupRighitIndex.SuspendLayout();
            this.groupLeftIndex.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.leftStateDataGrid)).BeginInit();
            this.groupRunningIndex.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.runninngIndexGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // createSW
            // 
            this.createSW.Location = new System.Drawing.Point(642, 454);
            this.createSW.Name = "createSW";
            this.createSW.Size = new System.Drawing.Size(75, 23);
            this.createSW.TabIndex = 0;
            this.createSW.Text = "CREATE";
            this.createSW.UseVisualStyleBackColor = true;
            this.createSW.Click += new System.EventHandler(this.createSW_Click);
            // 
            // textBoxSpdP
            // 
            this.textBoxSpdP.Location = new System.Drawing.Point(43, 33);
            this.textBoxSpdP.Name = "textBoxSpdP";
            this.textBoxSpdP.Size = new System.Drawing.Size(55, 19);
            this.textBoxSpdP.TabIndex = 1;
            // 
            // textBoxSpdI
            // 
            this.textBoxSpdI.Location = new System.Drawing.Point(43, 72);
            this.textBoxSpdI.Name = "textBoxSpdI";
            this.textBoxSpdI.Size = new System.Drawing.Size(55, 19);
            this.textBoxSpdI.TabIndex = 2;
            // 
            // textBoxSpdD
            // 
            this.textBoxSpdD.Location = new System.Drawing.Point(43, 115);
            this.textBoxSpdD.Name = "textBoxSpdD";
            this.textBoxSpdD.Size = new System.Drawing.Size(55, 19);
            this.textBoxSpdD.TabIndex = 3;
            // 
            // textBoxDegD
            // 
            this.textBoxDegD.Location = new System.Drawing.Point(56, 108);
            this.textBoxDegD.Name = "textBoxDegD";
            this.textBoxDegD.Size = new System.Drawing.Size(55, 19);
            this.textBoxDegD.TabIndex = 6;
            // 
            // textBoxDegI
            // 
            this.textBoxDegI.Location = new System.Drawing.Point(56, 65);
            this.textBoxDegI.Name = "textBoxDegI";
            this.textBoxDegI.Size = new System.Drawing.Size(55, 19);
            this.textBoxDegI.TabIndex = 5;
            // 
            // textBoxDegP
            // 
            this.textBoxDegP.Location = new System.Drawing.Point(56, 26);
            this.textBoxDegP.Name = "textBoxDegP";
            this.textBoxDegP.Size = new System.Drawing.Size(55, 19);
            this.textBoxDegP.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(12, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "P";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 118);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "D";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(8, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "I";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(34, 65);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(8, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "I";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(34, 108);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(13, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "D";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(34, 26);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(12, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "P";
            // 
            // groupSpd
            // 
            this.groupSpd.Controls.Add(this.label3);
            this.groupSpd.Controls.Add(this.label2);
            this.groupSpd.Controls.Add(this.label1);
            this.groupSpd.Controls.Add(this.textBoxSpdD);
            this.groupSpd.Controls.Add(this.textBoxSpdI);
            this.groupSpd.Controls.Add(this.textBoxSpdP);
            this.groupSpd.Location = new System.Drawing.Point(18, 16);
            this.groupSpd.Name = "groupSpd";
            this.groupSpd.Size = new System.Drawing.Size(120, 170);
            this.groupSpd.TabIndex = 13;
            this.groupSpd.TabStop = false;
            this.groupSpd.Text = "SPEED";
            // 
            // groupDeg
            // 
            this.groupDeg.Controls.Add(this.label4);
            this.groupDeg.Controls.Add(this.label5);
            this.groupDeg.Controls.Add(this.label6);
            this.groupDeg.Controls.Add(this.textBoxDegD);
            this.groupDeg.Controls.Add(this.textBoxDegI);
            this.groupDeg.Controls.Add(this.textBoxDegP);
            this.groupDeg.Location = new System.Drawing.Point(169, 16);
            this.groupDeg.Name = "groupDeg";
            this.groupDeg.Size = new System.Drawing.Size(120, 170);
            this.groupDeg.TabIndex = 14;
            this.groupDeg.TabStop = false;
            this.groupDeg.Text = "DEGREE";
            // 
            // righitStateDataGrid
            // 
            this.righitStateDataGrid.AllowDrop = true;
            this.righitStateDataGrid.AllowUserToAddRows = false;
            this.righitStateDataGrid.AllowUserToDeleteRows = false;
            this.righitStateDataGrid.AllowUserToResizeColumns = false;
            this.righitStateDataGrid.AllowUserToResizeRows = false;
            this.righitStateDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.righitStateDataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.RIdxNo,
            this.RIdxNextCond,
            this.RIdxCoundValue,
            this.RIdxActNo,
            this.RIdxNextNo});
            this.righitStateDataGrid.Location = new System.Drawing.Point(21, 23);
            this.righitStateDataGrid.Name = "righitStateDataGrid";
            this.righitStateDataGrid.RowTemplate.Height = 21;
            this.righitStateDataGrid.Size = new System.Drawing.Size(368, 150);
            this.righitStateDataGrid.TabIndex = 15;
            this.righitStateDataGrid.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.righitStateDataGrid_CellParsing);
            // 
            // RIdxNo
            // 
            this.RIdxNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            dataGridViewCellStyle3.Format = "0";
            dataGridViewCellStyle3.NullValue = "0";
            this.RIdxNo.DefaultCellStyle = dataGridViewCellStyle3;
            this.RIdxNo.HeaderText = "No";
            this.RIdxNo.Name = "RIdxNo";
            this.RIdxNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxNo.Width = 25;
            // 
            // RIdxNextCond
            // 
            this.RIdxNextCond.AutoComplete = false;
            this.RIdxNextCond.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.RIdxNextCond.HeaderText = "NextCond";
            this.RIdxNextCond.Name = "RIdxNextCond";
            // 
            // RIdxCoundValue
            // 
            this.RIdxCoundValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxCoundValue.HeaderText = "CoundValue";
            this.RIdxCoundValue.Name = "RIdxCoundValue";
            this.RIdxCoundValue.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxCoundValue.Width = 72;
            // 
            // RIdxActNo
            // 
            this.RIdxActNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxActNo.HeaderText = "ActNo";
            this.RIdxActNo.Name = "RIdxActNo";
            this.RIdxActNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxActNo.Width = 43;
            // 
            // RIdxNextNo
            // 
            this.RIdxNextNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxNextNo.HeaderText = "NextNo";
            this.RIdxNextNo.Name = "RIdxNextNo";
            this.RIdxNextNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxNextNo.Width = 49;
            // 
            // groupRighitIndex
            // 
            this.groupRighitIndex.Controls.Add(this.RIdxSortSw);
            this.groupRighitIndex.Controls.Add(this.righitStateDataGrid);
            this.groupRighitIndex.Location = new System.Drawing.Point(305, 16);
            this.groupRighitIndex.Name = "groupRighitIndex";
            this.groupRighitIndex.Size = new System.Drawing.Size(412, 208);
            this.groupRighitIndex.TabIndex = 16;
            this.groupRighitIndex.TabStop = false;
            this.groupRighitIndex.Text = "RIGHIT_INDEX";
            // 
            // RIdxSortSw
            // 
            this.RIdxSortSw.Location = new System.Drawing.Point(314, 179);
            this.RIdxSortSw.Name = "RIdxSortSw";
            this.RIdxSortSw.Size = new System.Drawing.Size(75, 23);
            this.RIdxSortSw.TabIndex = 16;
            this.RIdxSortSw.Text = "ReSORT";
            this.RIdxSortSw.UseVisualStyleBackColor = true;
            this.RIdxSortSw.Click += new System.EventHandler(this.RIdxSortSw_Click);
            // 
            // groupLeftIndex
            // 
            this.groupLeftIndex.Controls.Add(this.LIdxSortSw);
            this.groupLeftIndex.Controls.Add(this.leftStateDataGrid);
            this.groupLeftIndex.Location = new System.Drawing.Point(305, 238);
            this.groupLeftIndex.Name = "groupLeftIndex";
            this.groupLeftIndex.Size = new System.Drawing.Size(412, 208);
            this.groupLeftIndex.TabIndex = 17;
            this.groupLeftIndex.TabStop = false;
            this.groupLeftIndex.Text = "LEFT_INDEX";
            // 
            // LIdxSortSw
            // 
            this.LIdxSortSw.Location = new System.Drawing.Point(314, 179);
            this.LIdxSortSw.Name = "LIdxSortSw";
            this.LIdxSortSw.Size = new System.Drawing.Size(75, 23);
            this.LIdxSortSw.TabIndex = 17;
            this.LIdxSortSw.Text = "ReSORT";
            this.LIdxSortSw.UseVisualStyleBackColor = true;
            this.LIdxSortSw.Click += new System.EventHandler(this.LIdxSortSw_Click);
            // 
            // leftStateDataGrid
            // 
            this.leftStateDataGrid.AllowUserToAddRows = false;
            this.leftStateDataGrid.AllowUserToDeleteRows = false;
            this.leftStateDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.leftStateDataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LIdxNo,
            this.LIdxNextCond,
            this.LIdxCoundValue,
            this.LIdxActNo,
            this.LIdxNextNo});
            this.leftStateDataGrid.Location = new System.Drawing.Point(21, 23);
            this.leftStateDataGrid.Name = "leftStateDataGrid";
            this.leftStateDataGrid.RowTemplate.Height = 21;
            this.leftStateDataGrid.Size = new System.Drawing.Size(368, 150);
            this.leftStateDataGrid.TabIndex = 15;
            this.leftStateDataGrid.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.leftStateDataGrid_CellParsing);
            // 
            // LIdxNo
            // 
            this.LIdxNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.LIdxNo.HeaderText = "No";
            this.LIdxNo.Name = "LIdxNo";
            this.LIdxNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxNo.Width = 25;
            // 
            // LIdxNextCond
            // 
            this.LIdxNextCond.AutoComplete = false;
            this.LIdxNextCond.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.LIdxNextCond.HeaderText = "NextCond";
            this.LIdxNextCond.Name = "LIdxNextCond";
            // 
            // LIdxCoundValue
            // 
            this.LIdxCoundValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxCoundValue.HeaderText = "CoundValue";
            this.LIdxCoundValue.Name = "LIdxCoundValue";
            this.LIdxCoundValue.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxCoundValue.Width = 72;
            // 
            // LIdxActNo
            // 
            this.LIdxActNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxActNo.HeaderText = "ActNo";
            this.LIdxActNo.Name = "LIdxActNo";
            this.LIdxActNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxActNo.Width = 43;
            // 
            // LIdxNextNo
            // 
            this.LIdxNextNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxNextNo.HeaderText = "NextNo";
            this.LIdxNextNo.Name = "LIdxNextNo";
            this.LIdxNextNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxNextNo.Width = 49;
            // 
            // loadSW
            // 
            this.loadSW.Location = new System.Drawing.Point(18, 454);
            this.loadSW.Name = "loadSW";
            this.loadSW.Size = new System.Drawing.Size(75, 23);
            this.loadSW.TabIndex = 18;
            this.loadSW.Text = "LOAD";
            this.loadSW.UseVisualStyleBackColor = true;
            this.loadSW.Click += new System.EventHandler(this.loadSW_Click);
            // 
            // ev3OpenFileDialog
            // 
            this.ev3OpenFileDialog.DefaultExt = "evs";
            this.ev3OpenFileDialog.Filter = "\"EV3設定ファイル (*.evs)|*.evs|すべてのファイル (*.*)|*.*\"";
            this.ev3OpenFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.ev3OpenFileDialog_FileOk);
            // 
            // groupRunningIndex
            // 
            this.groupRunningIndex.Controls.Add(this.runninngIndexGridView);
            this.groupRunningIndex.Location = new System.Drawing.Point(18, 205);
            this.groupRunningIndex.Name = "groupRunningIndex";
            this.groupRunningIndex.Size = new System.Drawing.Size(271, 241);
            this.groupRunningIndex.TabIndex = 19;
            this.groupRunningIndex.TabStop = false;
            this.groupRunningIndex.Text = "RUNNINNG_INDEX";
            // 
            // runninngIndexGridView
            // 
            this.runninngIndexGridView.AllowUserToAddRows = false;
            this.runninngIndexGridView.AllowUserToDeleteRows = false;
            this.runninngIndexGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.runninngIndexGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.RunNo,
            this.RunSpeed,
            this.RunTrun,
            this.RunTailDeg,
            this.RunBalance});
            this.runninngIndexGridView.Location = new System.Drawing.Point(15, 26);
            this.runninngIndexGridView.Name = "runninngIndexGridView";
            this.runninngIndexGridView.RowTemplate.Height = 21;
            this.runninngIndexGridView.Size = new System.Drawing.Size(240, 209);
            this.runninngIndexGridView.TabIndex = 0;
            this.runninngIndexGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.runninngIndexeDataGrid_CellParsing);
            // 
            // RunNo
            // 
            this.RunNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunNo.Frozen = true;
            this.RunNo.HeaderText = "No";
            this.RunNo.Name = "RunNo";
            this.RunNo.ReadOnly = true;
            this.RunNo.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunNo.Width = 25;
            // 
            // RunSpeed
            // 
            this.RunSpeed.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunSpeed.HeaderText = "Speed";
            this.RunSpeed.Name = "RunSpeed";
            this.RunSpeed.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunSpeed.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunSpeed.Width = 42;
            // 
            // RunTrun
            // 
            this.RunTrun.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunTrun.HeaderText = "Trun";
            this.RunTrun.Name = "RunTrun";
            this.RunTrun.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunTrun.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunTrun.Width = 34;
            // 
            // RunTailDeg
            // 
            this.RunTailDeg.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunTailDeg.HeaderText = "TailDeg";
            this.RunTailDeg.Name = "RunTailDeg";
            this.RunTailDeg.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunTailDeg.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunTailDeg.Width = 50;
            // 
            // RunBalance
            // 
            this.RunBalance.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.RunBalance.HeaderText = "Balance";
            this.RunBalance.Name = "RunBalance";
            this.RunBalance.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // ControlLabel
            // 
            this.ControlLabel.AutoEllipsis = true;
            this.ControlLabel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ControlLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ControlLabel.Location = new System.Drawing.Point(169, 455);
            this.ControlLabel.Margin = new System.Windows.Forms.Padding(0);
            this.ControlLabel.MaximumSize = new System.Drawing.Size(500, 500);
            this.ControlLabel.Name = "ControlLabel";
            this.ControlLabel.Padding = new System.Windows.Forms.Padding(10, 5, 10, 3);
            this.ControlLabel.Size = new System.Drawing.Size(400, 22);
            this.ControlLabel.TabIndex = 20;
            this.ControlLabel.Text = "デバッグ：NULL";
            this.ControlLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(727, 487);
            this.Controls.Add(this.ControlLabel);
            this.Controls.Add(this.groupRunningIndex);
            this.Controls.Add(this.loadSW);
            this.Controls.Add(this.groupLeftIndex);
            this.Controls.Add(this.groupRighitIndex);
            this.Controls.Add(this.groupDeg);
            this.Controls.Add(this.groupSpd);
            this.Controls.Add(this.createSW);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupSpd.ResumeLayout(false);
            this.groupSpd.PerformLayout();
            this.groupDeg.ResumeLayout(false);
            this.groupDeg.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.righitStateDataGrid)).EndInit();
            this.groupRighitIndex.ResumeLayout(false);
            this.groupLeftIndex.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.leftStateDataGrid)).EndInit();
            this.groupRunningIndex.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.runninngIndexGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button createSW;
        private System.Windows.Forms.TextBox textBoxSpdP;
        private System.Windows.Forms.TextBox textBoxSpdI;
        private System.Windows.Forms.TextBox textBoxSpdD;
        private System.Windows.Forms.TextBox textBoxDegD;
        private System.Windows.Forms.TextBox textBoxDegI;
        private System.Windows.Forms.TextBox textBoxDegP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupSpd;
        private System.Windows.Forms.GroupBox groupDeg;
        private System.Windows.Forms.DataGridView righitStateDataGrid;
        private System.Windows.Forms.GroupBox groupRighitIndex;
        private System.Windows.Forms.GroupBox groupLeftIndex;
        private System.Windows.Forms.DataGridView leftStateDataGrid;
        private System.Windows.Forms.Button RIdxSortSw;
        private System.Windows.Forms.Button LIdxSortSw;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxNo;
        private System.Windows.Forms.DataGridViewComboBoxColumn LIdxNextCond;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxCoundValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxActNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxNextNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxNo;
        private System.Windows.Forms.DataGridViewComboBoxColumn RIdxNextCond;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxCoundValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxActNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxNextNo;
        private System.Windows.Forms.Button loadSW;
        private System.Windows.Forms.OpenFileDialog ev3OpenFileDialog;
        private System.Windows.Forms.GroupBox groupRunningIndex;
        private System.Windows.Forms.DataGridView runninngIndexGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunSpeed;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunTrun;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunTailDeg;
        private System.Windows.Forms.DataGridViewCheckBoxColumn RunBalance;
        private System.Windows.Forms.Label ControlLabel;
    }
}

