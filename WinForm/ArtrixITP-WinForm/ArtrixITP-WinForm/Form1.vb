Imports System.Net
Imports System.Web
Imports System.Threading.Thread


Public Class Form1

    Dim thisServerID As String = "SER23333"

    Dim nowControlDevice As DeviceInfo

    Dim temp(30)
    Dim pres(30)
    Dim allDevices() = {}
    Dim tempIndex = 0
    Dim presIndex = 0

    Dim host = "iot.rapi.link:30126"
    Dim nowTemp, nowPress, nowHumi
    'Dim host = "http://localhost:5000"

    Sub GetServerData()

        nowTemp = Net.GetHTML(host + "/tempereature/CLI5F33Q")
        nowPress = Net.GetHTML(host + "/pressure/CLI5F33Q")
        nowHumi = Net.GetHTML(host + "/humidity/CLI5F33Q")

        allDevices = Net.GetHTML(host + "/device_list/" + thisServerID).split(",")

    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles NetUpdateTimer.Tick

        Dim tr As New Threading.Thread(AddressOf GetServerData)
        tr.Start()

    End Sub

    Dim themeColor = Color.White
    Function parseColor(img As Bitmap, color As Color)

        Dim temp As Bitmap
        temp = img
        For y = 0 To temp.Height - 1
            For x = 0 To temp.Width - 1
                If temp.GetPixel(x, y) = Color.FromArgb(0, 0, 0, 0) Then
                Else
                    temp.SetPixel(x, y, color)
                End If
            Next
        Next

        Return temp

    End Function
    Dim imgPres, imgTemp

    Dim nowHumiThres = 60
    Dim stepPerClick = 5
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles btnHumiThresAdd.Click
        If CInt(nowHumiThres <= 95) Then
            nowHumiThres += stepPerClick
        End If

    End Sub

    Sub deactiveSensorScreen()

        Label7.Hide()
        Label6.Hide()
        Label3.Hide()
        lblHumi.Hide()
        lblPres.Hide()
        lblTemp.Hide()

        iconTemp.Hide()
        iconPres.Hide()
        iconHumi.Hide()

    End Sub

    Sub activeSensorScreen()

        Label7.Show()
        Label6.Show()
        Label3.Show()
        lblHumi.Show()
        lblPres.Show()
        lblTemp.Show()

        iconTemp.Show()
        iconPres.Show()
        iconHumi.Show()

    End Sub

    Sub activeControllerScreen()

        btnLight.Show()

    End Sub

    Sub deactiveControllerScreen()

        btnLight.Hide()

    End Sub

    Private Sub Label9_Click(sender As Object, e As EventArgs) Handles btnCloseForm.Click
        Me.Dispose()
    End Sub



    Sub cli(obj As Object, e As EventArgs)

        Dim clickDevice = DeviceTypeDict(obj.Tag)
        If clickDevice.Type = DeviceType.SENSOR Then
            deactiveControllerScreen()
            activeSensorScreen()
            nowControlDevice = clickDevice
        End If

        If clickDevice.Type = DeviceType.CONTROLLER Then
            deactiveSensorScreen()
            activeControllerScreen()
            nowControlDevice = clickDevice
        End If
    End Sub
    Dim num = 0
    Function cloneButton(btnInput As Button)
        Dim btnOut As New Button
        btnOut.Size = btnInput.Size
        btnOut.Location = btnInput.Location
        btnOut.ForeColor = btnInput.ForeColor
        btnOut.FlatStyle = btnInput.FlatStyle
        btnOut.FlatAppearance.BorderColor = btnInput.FlatAppearance.BorderColor
        btnOut.FlatAppearance.BorderSize = btnInput.FlatAppearance.BorderSize
        btnOut.BackColor = btnInput.BackColor
        btnOut.Text = num
        btnOut.Font = btnInput.Font
        btnOut.Enabled = btnInput.Enabled
        AddHandler btnOut.Click, AddressOf cli
        num += 1
        Return btnOut
    End Function
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles btnHumiThresSubs.Click
        If CInt(nowHumiThres >= 5) Then
            nowHumiThres -= stepPerClick
        End If
    End Sub

    Dim lastUpdateBtnPool As New List(Of Button)

    Function ButtonExist(name As String)
        For i = 0 To lastUpdateBtnPool.Count - 1
            If lastUpdateBtnPool.Item(i).Tag = name Then
                'MessageBox.Show("In:" + lastUpdateBtnPool.Item(i).Text)
                Return i
            End If
        Next
        Return -1
    End Function

    Function DeviceExist(name As String)

        For i = 0 To allDevices.Count - 1
            If allDevices(i) = name Then
                Return i
            End If
        Next
        Return -1
    End Function

    Dim DeviceTypeDict As New Dictionary(Of String, DeviceInfo)

    Dim lightState = False
    Private Sub btnLight_Click(sender As Object, e As EventArgs) Handles btnLight.Click
        Dim id = nowControlDevice.DEVICE_ID
        Dim sendMsg = ""

        If lightState Then

            sendMsg = "##DOWNLINK##S,DOWNLINK,SETPWR,"
            sendMsg += id
            sendMsg += ",OFF,END|"

            lightState = False
            btnLight.Text = "OFF"

        Else

            sendMsg = "##DOWNLINK##S,DOWNLINK,SETPWR,"
            sendMsg += id
            sendMsg += ",ON,END|"

            lightState = True
            btnLight.Text = "ON"

        End If



        Dim urlEnc = System.Net.WebUtility.UrlEncode(sendMsg)
        Dim result = Net.GetHTML(host + "/control/" + id + "/" + urlEnc)
        Threading.Thread.Sleep(20)
        result = Net.GetHTML(host + "/control/" + id + "/" + urlEnc)


    End Sub

    Function GetDeviceType(name As String)
        If DeviceTypeDict.ContainsKey(name) Then
            Return DeviceTypeDict(name)
        End If
        Return New DeviceInfo("CLI00000", "未知类型设备", DeviceType.UNKNOWN)
    End Function
    Private Sub UIUpdateTimer_Tick(sender As Object, e As EventArgs) Handles UIUpdateTimer.Tick

        lblTemp.Text = nowTemp

        lblPres.Text = nowPress
        lblHumi.Text = nowHumi
        lblHumiThres.Text = CStr(nowHumiThres) + "%"

        If allDevices.Count > 0 Then

            Try

                For i = 0 To lastUpdateBtnPool.Count - 1
                    If DeviceExist(lastUpdateBtnPool.Item(i).Tag) = -1 Then
                        lastUpdateBtnPool.Item(i).Visible = False
                        lastUpdateBtnPool.Item(i).Dispose()
                        lastUpdateBtnPool.RemoveAt(i)
                    End If
                Next


                For i = 0 To allDevices.Count - 1

                    If ButtonExist(allDevices(i)) = -1 Then

                        If Not allDevices(i) = "" Then

                            Dim q = cloneButton(btnDevice_Template)

                            q.Visible = True
                            q.Text = allDevices(i) + “ - ” + GetDeviceType(allDevices(i)).Description
                            q.Tag = allDevices(i)

                            lastUpdateBtnPool.Add(q)
                            FlowLayoutPanel1.Controls.Add(q)
                        End If

                    End If

                Next

            Catch ex As Exception

            End Try
        End If

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        DeviceTypeDict("CLI5F33Q") = New DeviceInfo("CLI5F33Q", "气象传感终端", DeviceType.SENSOR)
        DeviceTypeDict("CLI6E55S") = New DeviceInfo("CLI6E55S", "主卧灯光控制", DeviceType.CONTROLLER)
        DeviceTypeDict("CLIQR3FF") = New DeviceInfo("CLIQR3FF", "客厅空净控制", DeviceType.CONTROLLER)
        DeviceTypeDict("CLI6M5E4") = New DeviceInfo("CLI6M5E4", "土壤湿度终端", DeviceType.SENSOR)
        imgTemp = parseColor(My.Resources.temp, themeColor)
        imgPres = parseColor(My.Resources.pres, themeColor)
        iconPres.Image = imgPres
        iconTemp.Image = imgTemp

    End Sub
End Class


Enum DeviceType
    CONTROLLER = 0
    SENSOR = 1
    UNKNOWN = -1
End Enum

Structure DeviceInfo

    Public Description As String
    Public Type As DeviceType
    Public DEVICE_ID As String

    Public Sub New(deviceID As String, description As String, type As DeviceType)
        Me.Description = description
        Me.Type = type
        Me.DEVICE_ID = deviceID
    End Sub

End Structure

Class Net
    Shared Function GetHTML(URL As String)
        Dim rq As HttpWebRequest
        Try
            If InStr(URL, "http://") Then
                rq = WebRequest.Create(URL)
            Else
                rq = WebRequest.Create("http://" & URL)
            End If
        Catch ex As Exception
            Return False
            Exit Function
        End Try

        'MessageBox.Show(rq.ToString)
        Try


            Dim rp As HttpWebResponse = rq.GetResponse()
            Dim reader As IO.StreamReader = New IO.StreamReader(rp.GetResponseStream())
            Dim resourceString = reader.ReadToEnd

            Console.WriteLine(resourceString)
            Return resourceString
        Catch ex As Exception

        End Try
        Return "NAN"
    End Function
End Class


