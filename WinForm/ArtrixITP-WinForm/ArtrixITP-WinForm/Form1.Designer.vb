<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.lblTemp = New System.Windows.Forms.Label()
        Me.NetUpdateTimer = New System.Windows.Forms.Timer(Me.components)
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.lblPres = New System.Windows.Forms.Label()
        Me.iconPres = New System.Windows.Forms.PictureBox()
        Me.iconTemp = New System.Windows.Forms.PictureBox()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.ListView1 = New System.Windows.Forms.ListView()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.iconHumi = New System.Windows.Forms.PictureBox()
        Me.lblHumi = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.PictureBox3 = New System.Windows.Forms.PictureBox()
        Me.lblHumiThres = New System.Windows.Forms.Label()
        Me.btnHumiThresAdd = New System.Windows.Forms.Button()
        Me.btnHumiThresSubs = New System.Windows.Forms.Button()
        Me.UIUpdateTimer = New System.Windows.Forms.Timer(Me.components)
        Me.btnCloseForm = New System.Windows.Forms.Label()
        Me.FlowLayoutPanel1 = New System.Windows.Forms.FlowLayoutPanel()
        Me.btnDevice_Template = New System.Windows.Forms.Button()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.btnLight = New System.Windows.Forms.Button()
        CType(Me.iconPres, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.iconTemp, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.iconHumi, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'lblTemp
        '
        Me.lblTemp.AutoSize = True
        Me.lblTemp.BackColor = System.Drawing.Color.Transparent
        Me.lblTemp.Font = New System.Drawing.Font("Flexo Thin", 36.0!)
        Me.lblTemp.ForeColor = System.Drawing.Color.White
        Me.lblTemp.Location = New System.Drawing.Point(132, 84)
        Me.lblTemp.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblTemp.Name = "lblTemp"
        Me.lblTemp.Size = New System.Drawing.Size(178, 72)
        Me.lblTemp.TabIndex = 0
        Me.lblTemp.Text = "32.60"
        '
        'NetUpdateTimer
        '
        Me.NetUpdateTimer.Enabled = True
        Me.NetUpdateTimer.Interval = 1500
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.BackColor = System.Drawing.Color.Transparent
        Me.Label2.Font = New System.Drawing.Font("Flexo", 18.0!)
        Me.Label2.ForeColor = System.Drawing.Color.SteelBlue
        Me.Label2.Location = New System.Drawing.Point(551, 201)
        Me.Label2.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(42, 36)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "°C"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.BackColor = System.Drawing.Color.Transparent
        Me.Label3.Font = New System.Drawing.Font("Flexo Light", 12.0!)
        Me.Label3.ForeColor = System.Drawing.Color.White
        Me.Label3.Location = New System.Drawing.Point(140, 178)
        Me.Label3.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(45, 24)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "hPa"
        '
        'lblPres
        '
        Me.lblPres.AutoSize = True
        Me.lblPres.BackColor = System.Drawing.Color.Transparent
        Me.lblPres.Font = New System.Drawing.Font("Flexo Thin", 34.0!)
        Me.lblPres.ForeColor = System.Drawing.Color.White
        Me.lblPres.Location = New System.Drawing.Point(132, 198)
        Me.lblPres.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblPres.Name = "lblPres"
        Me.lblPres.Size = New System.Drawing.Size(214, 68)
        Me.lblPres.TabIndex = 4
        Me.lblPres.Text = "1014.26"
        '
        'iconPres
        '
        Me.iconPres.BackColor = System.Drawing.Color.Transparent
        Me.iconPres.Image = Global.WindowsApp1.My.Resources.Resources.pres
        Me.iconPres.Location = New System.Drawing.Point(55, 178)
        Me.iconPres.Margin = New System.Windows.Forms.Padding(4)
        Me.iconPres.Name = "iconPres"
        Me.iconPres.Size = New System.Drawing.Size(88, 82)
        Me.iconPres.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.iconPres.TabIndex = 5
        Me.iconPres.TabStop = False
        '
        'iconTemp
        '
        Me.iconTemp.BackColor = System.Drawing.Color.Transparent
        Me.iconTemp.Image = Global.WindowsApp1.My.Resources.Resources.temp
        Me.iconTemp.Location = New System.Drawing.Point(55, 74)
        Me.iconTemp.Margin = New System.Windows.Forms.Padding(4)
        Me.iconTemp.Name = "iconTemp"
        Me.iconTemp.Size = New System.Drawing.Size(88, 82)
        Me.iconTemp.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.iconTemp.TabIndex = 2
        Me.iconTemp.TabStop = False
        '
        'PictureBox1
        '
        Me.PictureBox1.BackColor = System.Drawing.Color.White
        Me.PictureBox1.Location = New System.Drawing.Point(-3, -1)
        Me.PictureBox1.Margin = New System.Windows.Forms.Padding(4)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(1003, 24)
        Me.PictureBox1.TabIndex = 1
        Me.PictureBox1.TabStop = False
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.BackColor = System.Drawing.Color.White
        Me.Label5.Font = New System.Drawing.Font("Microsoft YaHei UI", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.Label5.ForeColor = System.Drawing.Color.SteelBlue
        Me.Label5.Location = New System.Drawing.Point(5, 0)
        Me.Label5.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(141, 20)
        Me.Label5.TabIndex = 7
        Me.Label5.Text = "ArtrixITP-SER2333"
        '
        'ListView1
        '
        Me.ListView1.BackgroundImage = Global.WindowsApp1.My.Resources.Resources.un221
        Me.ListView1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.ListView1.Location = New System.Drawing.Point(785, 41)
        Me.ListView1.Margin = New System.Windows.Forms.Padding(4)
        Me.ListView1.Name = "ListView1"
        Me.ListView1.Size = New System.Drawing.Size(240, 468)
        Me.ListView1.TabIndex = 8
        Me.ListView1.UseCompatibleStateImageBehavior = False
        Me.ListView1.Visible = False
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.BackColor = System.Drawing.Color.Transparent
        Me.Label6.Font = New System.Drawing.Font("Flexo Light", 12.0!)
        Me.Label6.ForeColor = System.Drawing.Color.White
        Me.Label6.Location = New System.Drawing.Point(140, 70)
        Me.Label6.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(28, 24)
        Me.Label6.TabIndex = 9
        Me.Label6.Text = "°C"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.BackColor = System.Drawing.Color.Transparent
        Me.Label7.Font = New System.Drawing.Font("Flexo Light", 12.0!)
        Me.Label7.ForeColor = System.Drawing.Color.White
        Me.Label7.Location = New System.Drawing.Point(140, 282)
        Me.Label7.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(26, 24)
        Me.Label7.TabIndex = 12
        Me.Label7.Text = "%"
        '
        'iconHumi
        '
        Me.iconHumi.BackColor = System.Drawing.Color.Transparent
        Me.iconHumi.Image = Global.WindowsApp1.My.Resources.Resources.水
        Me.iconHumi.Location = New System.Drawing.Point(63, 289)
        Me.iconHumi.Margin = New System.Windows.Forms.Padding(4)
        Me.iconHumi.Name = "iconHumi"
        Me.iconHumi.Size = New System.Drawing.Size(69, 70)
        Me.iconHumi.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.iconHumi.TabIndex = 11
        Me.iconHumi.TabStop = False
        '
        'lblHumi
        '
        Me.lblHumi.AutoSize = True
        Me.lblHumi.BackColor = System.Drawing.Color.Transparent
        Me.lblHumi.Font = New System.Drawing.Font("Flexo Thin", 34.0!)
        Me.lblHumi.ForeColor = System.Drawing.Color.White
        Me.lblHumi.Location = New System.Drawing.Point(132, 302)
        Me.lblHumi.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblHumi.Name = "lblHumi"
        Me.lblHumi.Size = New System.Drawing.Size(174, 68)
        Me.lblHumi.TabIndex = 10
        Me.lblHumi.Text = "78.00"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.BackColor = System.Drawing.Color.Transparent
        Me.Label10.Font = New System.Drawing.Font("Flexo Light", 8.0!)
        Me.Label10.ForeColor = System.Drawing.Color.White
        Me.Label10.Location = New System.Drawing.Point(627, 35)
        Me.Label10.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(95, 17)
        Me.Label10.TabIndex = 16
        Me.Label10.Text = "Threshold - %"
        '
        'PictureBox3
        '
        Me.PictureBox3.BackColor = System.Drawing.Color.Transparent
        Me.PictureBox3.Image = Global.WindowsApp1.My.Resources.Resources.水
        Me.PictureBox3.Location = New System.Drawing.Point(577, 31)
        Me.PictureBox3.Margin = New System.Windows.Forms.Padding(4)
        Me.PictureBox3.Name = "PictureBox3"
        Me.PictureBox3.Size = New System.Drawing.Size(44, 47)
        Me.PictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.PictureBox3.TabIndex = 15
        Me.PictureBox3.TabStop = False
        '
        'lblHumiThres
        '
        Me.lblHumiThres.AutoSize = True
        Me.lblHumiThres.BackColor = System.Drawing.Color.Transparent
        Me.lblHumiThres.Font = New System.Drawing.Font("Flexo Thin", 18.0!)
        Me.lblHumiThres.ForeColor = System.Drawing.Color.White
        Me.lblHumiThres.Location = New System.Drawing.Point(624, 47)
        Me.lblHumiThres.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblHumiThres.Name = "lblHumiThres"
        Me.lblHumiThres.Size = New System.Drawing.Size(87, 36)
        Me.lblHumiThres.TabIndex = 14
        Me.lblHumiThres.Text = "100%"
        '
        'btnHumiThresAdd
        '
        Me.btnHumiThresAdd.BackColor = System.Drawing.Color.Transparent
        Me.btnHumiThresAdd.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.btnHumiThresAdd.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnHumiThresAdd.Font = New System.Drawing.Font("Microsoft Sans Serif", 5.0!)
        Me.btnHumiThresAdd.ForeColor = System.Drawing.Color.White
        Me.btnHumiThresAdd.Location = New System.Drawing.Point(712, 54)
        Me.btnHumiThresAdd.Name = "btnHumiThresAdd"
        Me.btnHumiThresAdd.Size = New System.Drawing.Size(20, 20)
        Me.btnHumiThresAdd.TabIndex = 17
        Me.btnHumiThresAdd.Text = "+"
        Me.btnHumiThresAdd.UseVisualStyleBackColor = False
        '
        'btnHumiThresSubs
        '
        Me.btnHumiThresSubs.BackColor = System.Drawing.Color.Transparent
        Me.btnHumiThresSubs.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.btnHumiThresSubs.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnHumiThresSubs.Font = New System.Drawing.Font("Microsoft Sans Serif", 5.0!)
        Me.btnHumiThresSubs.ForeColor = System.Drawing.Color.White
        Me.btnHumiThresSubs.Location = New System.Drawing.Point(738, 54)
        Me.btnHumiThresSubs.Name = "btnHumiThresSubs"
        Me.btnHumiThresSubs.Size = New System.Drawing.Size(20, 20)
        Me.btnHumiThresSubs.TabIndex = 18
        Me.btnHumiThresSubs.Text = "-"
        Me.btnHumiThresSubs.UseVisualStyleBackColor = False
        '
        'UIUpdateTimer
        '
        Me.UIUpdateTimer.Enabled = True
        '
        'btnCloseForm
        '
        Me.btnCloseForm.AutoSize = True
        Me.btnCloseForm.BackColor = System.Drawing.Color.White
        Me.btnCloseForm.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnCloseForm.Font = New System.Drawing.Font("Microsoft YaHei UI", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.btnCloseForm.ForeColor = System.Drawing.Color.SteelBlue
        Me.btnCloseForm.Location = New System.Drawing.Point(898, 0)
        Me.btnCloseForm.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.btnCloseForm.Name = "btnCloseForm"
        Me.btnCloseForm.Size = New System.Drawing.Size(19, 20)
        Me.btnCloseForm.TabIndex = 19
        Me.btnCloseForm.Text = "X"
        '
        'FlowLayoutPanel1
        '
        Me.FlowLayoutPanel1.BackColor = System.Drawing.Color.Transparent
        Me.FlowLayoutPanel1.Location = New System.Drawing.Point(6, 25)
        Me.FlowLayoutPanel1.Name = "FlowLayoutPanel1"
        Me.FlowLayoutPanel1.Size = New System.Drawing.Size(501, 86)
        Me.FlowLayoutPanel1.TabIndex = 20
        '
        'btnDevice_Template
        '
        Me.btnDevice_Template.BackColor = System.Drawing.Color.Transparent
        Me.btnDevice_Template.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.btnDevice_Template.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnDevice_Template.Font = New System.Drawing.Font("Microsoft Sans Serif", 7.8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnDevice_Template.ForeColor = System.Drawing.Color.White
        Me.btnDevice_Template.Location = New System.Drawing.Point(383, 41)
        Me.btnDevice_Template.Name = "btnDevice_Template"
        Me.btnDevice_Template.Size = New System.Drawing.Size(234, 30)
        Me.btnDevice_Template.TabIndex = 21
        Me.btnDevice_Template.Text = "CLI5F33Q - 传感终端"
        Me.btnDevice_Template.UseVisualStyleBackColor = False
        Me.btnDevice_Template.Visible = False
        '
        'GroupBox1
        '
        Me.GroupBox1.BackColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer))
        Me.GroupBox1.Controls.Add(Me.FlowLayoutPanel1)
        Me.GroupBox1.Font = New System.Drawing.Font("Microsoft YaHei UI Light", 9.070867!)
        Me.GroupBox1.ForeColor = System.Drawing.Color.White
        Me.GroupBox1.Location = New System.Drawing.Point(369, 84)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(513, 117)
        Me.GroupBox1.TabIndex = 22
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Now Online 当前在线"
        '
        'btnLight
        '
        Me.btnLight.BackColor = System.Drawing.Color.Transparent
        Me.btnLight.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.btnLight.FlatAppearance.BorderSize = 2
        Me.btnLight.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(CType(CType(100, Byte), Integer), CType(CType(64, Byte), Integer), CType(CType(64, Byte), Integer), CType(CType(64, Byte), Integer))
        Me.btnLight.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(CType(CType(100, Byte), Integer), CType(CType(64, Byte), Integer), CType(CType(64, Byte), Integer), CType(CType(64, Byte), Integer))
        Me.btnLight.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnLight.Font = New System.Drawing.Font("Flexo", 18.0!)
        Me.btnLight.ForeColor = System.Drawing.Color.White
        Me.btnLight.Location = New System.Drawing.Point(123, 158)
        Me.btnLight.Name = "btnLight"
        Me.btnLight.Size = New System.Drawing.Size(102, 92)
        Me.btnLight.TabIndex = 23
        Me.btnLight.Text = "OFF"
        Me.btnLight.UseVisualStyleBackColor = False
        Me.btnLight.Visible = False
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.White
        Me.BackgroundImage = Global.WindowsApp1.My.Resources.Resources.un2_nof
        Me.ClientSize = New System.Drawing.Size(919, 420)
        Me.Controls.Add(Me.btnLight)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.btnDevice_Template)
        Me.Controls.Add(Me.btnCloseForm)
        Me.Controls.Add(Me.btnHumiThresSubs)
        Me.Controls.Add(Me.btnHumiThresAdd)
        Me.Controls.Add(Me.Label10)
        Me.Controls.Add(Me.PictureBox3)
        Me.Controls.Add(Me.lblHumiThres)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.iconHumi)
        Me.Controls.Add(Me.lblHumi)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.ListView1)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.iconPres)
        Me.Controls.Add(Me.lblPres)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.iconTemp)
        Me.Controls.Add(Me.lblTemp)
        Me.Controls.Add(Me.PictureBox1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Form1"
        CType(Me.iconPres, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.iconTemp, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.iconHumi, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents lblTemp As Label
    Friend WithEvents NetUpdateTimer As Timer
    Friend WithEvents PictureBox1 As PictureBox
    Friend WithEvents iconTemp As PictureBox
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents iconPres As PictureBox
    Friend WithEvents lblPres As Label
    Friend WithEvents Label5 As Label
    Friend WithEvents ListView1 As ListView
    Friend WithEvents Label6 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents iconHumi As PictureBox
    Friend WithEvents lblHumi As Label
    Friend WithEvents Label10 As Label
    Friend WithEvents PictureBox3 As PictureBox
    Friend WithEvents lblHumiThres As Label
    Friend WithEvents btnHumiThresAdd As Button
    Friend WithEvents btnHumiThresSubs As Button
    Friend WithEvents UIUpdateTimer As Timer
    Friend WithEvents btnCloseForm As Label
    Friend WithEvents FlowLayoutPanel1 As FlowLayoutPanel
    Friend WithEvents btnDevice_Template As Button
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents btnLight As Button
End Class
