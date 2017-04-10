C-Mikrocontroller

Der Code auf Microcontrollerseite besteht aus zwei Dateien. Der main.c und der utils.h. In der utils.h sind lediglich einige ausgelagerte Funktionen zu finden, welche zum größten Teil im Praktikum bei vorherigen Aufgaben erarbeitet wurden. Hinzugekommen sind einmal die "lcd_drawPixelDirect", welche den Pixel zunächst in den Framebuffer schreibt und dann direkt an das Display überträgt. Weiterhin sind im unteren Teil der Headerdatei einige Funktionen im Bezug auf die UART Schnittstelle zu finden. "InitUart1" initialisiert die UART Schnittstelle und setzt Standardparameter wie die Baudrate, Paritätsbit, Stopbit, etc. (Aktuelle Konfiguration ist 115200Baud 8N1). Die Funktionen "Putch1", "Getch1", "Puts1" stellen Kommunikationsschnittstellen mit der UART dar.
In der main.c werden zunächst die Initialisierungsfunktionen aufgerufen, um das Display und die UART zu initialisieren. Danach wird der Splashscreen mittels "lcd_splash()" in den Framebuffer geladen und per "lcd_flush()" auf das Display geschrieben.
In der Mainloop wird nun immer auf ein neues Byte im UART Buffer gewartet. Hierfür muss der Ausdruck "SSR1_RDRF != 0" zu true ausgewertet werden.
Wurde ein Zeichen empfangen, wird es in einer Art Statemachine verarbeitet:
Es existieren 3 Zustände: idle(0x00), setPixel(0xAA) und framebuffer(0xBB). Diese werden jeweils in die Variable "mode" geschrieben, um den aktuellen Zustand zu speichern.
Ist die Statemachine im idle(0x00) Zustand, erwartet sie also entweder ein 0xAA oder ein 0xBB um in einen der anderen Modi zu wechseln. Wurde eines der beiden Bytes empfangen, wird mode dementsprechend geändert.
Je nach dem in welchem Mode die STM sich nun befindet, werden kommende Bytes unterschiedlich interpretiert:
Im setPixel(0xAA) Mode, enthalten die kommenden 3 Byte die Informationen "x-Koordinate", "y-Koordinate", "Wert (1=An, 0=aus)".
Ist das komplette 3er Tuple empfangen, wird die "lcd_drawPixelDirect()" Methode mit den 3 Werten aufgerufen und der Pixel gemalt. Danach geht die STM wieder in den idle(0x00) Mode, um auf eine neue Eingabe zu warten.
Im framebuffer Mode, erwartet der Microcontroller einen kompletten Framebuffer. Alle kommenden Bytes werden direkt in den lcd_buffer geschrieben, bis dieser voll ist. Ist der Buffer voll, wird "lcd_flush()" aufgerufen und der Buffer auf das Display geschrieben.
Die STM geht nun wieder in den idle(0x00) Mode.


Java Projekt SerialTest

Das Java Projekt beinhaltet lediglich eine .java Datei, nämlich "TwoWaySerialComm.java". Diese basiert auf einem Beispiel, welches ich im Internet gefunden habe. Zur Ausführung, wird noch die Library "RXTXcomm" benötigt.
Das Programm an sich arbeitet mit einer Zählvariable, welche immer von 0 bis 7 läuft. Um diese Zählvariable wird dann eine 1 nach links geshifted und in das Bytearray geschrieben, welches später rausgeschickt wird.
Dadurch entsteht dieser "Laufeffekt", da ein Byte ja immer 8 Zeilen darstellt.



C#-Projekte Serial und SerialImage

Serial
Dieses Programm sendet per serieller Verbindung die Mausspur an das Board. Die Mausspur wird in der Klasse RemoteDisplay gespeichert als verkettete Liste. Wenn die Mausspur verlängert wird, wird das Event MouseTrackAddEventgeworfen und beim Entfernen eines Punktes aus der Mausspur das Event MouseTrackDeleteEvent. Zu beiden Events existieren Event-Parameter Klassen die alle notwendigen Informationen über eingefügte oder entfernte Punkte enthalten (MouseTrackAddEventArgs, MouseTrackDeleteEventArgs).

Die Klasse Form1 stellt das eigentliche Benutzerformular dar und enthält eine RemoteDisplay Instanz zehn mal so groß wie das tatsächliche Display auf dem Board. Es registriert sich als Event-Listener für o.g. Mausspur Events von RemoteDisplay. Beim Start des Formulars wird der Benutzer aufgefordert einen COM-Port für die serielle Verbindung auszuwählen. Wird kein Port ausgewählt, wird das Programm beendet. Die serielle Verbindung ist ebenfalls eine Instanz innerhalb der Form1 Klasse. Es ist eine Standard Klasse des .Net Frameworks. Ich habe mich dafür entschieden, dass die Konfiguration im Formular-Designer vorgenommen werden muss, da ich nicht mehr genug Zeit für eine komfortable Eingabemaske hatte. An dieser Stelle besteht Verbesserungsbedarf. Die wichtigste Methode der Form1 Klasse ist private void SendSerial(int x, int y, bool on). Hier werden eingehende Pixel Koordinaten runter skaliert um Werte innerhalb der tatsächlichen Bildschirmgröße des Board anzunehmen. Ebenfalls wichtig ist, dass der erste Buffer-Eintrag für ein Datenpaket immer 0xAA (Modus A) enthalten muss.

SerialImage
Auch in diesem Projekt ist die Klasse Form1 das eigentlich Benutzerformular. Es enthält einen Button und eine Picture-Box für die Vorschau des übertragenen Bildes. Beim Start des Formulars wird der Benutzer aufgefordert einen COM-Port für die serielle Verbindung auszuwählen. Wird kein Port ausgewählt, wird das Programm beendet. Beim drücken des Buttons wird der Benutzer aufgefordert eine Bilddatei auszuwählen. Dieses Bild wird anschließend binärisiert, sodass es nur noch aus schwarzen und weißen Pixeln besteht. Anschließend wird das Bild verkleinert, sodass es die Auflösung des Bildschirms auf dem Board hat (diese Reihenfolge sollte ggf. getauscht werden). Danach wird die serielle Verbindung geöffnet, das Bild in den Buffer bufferTransferModeB transferiert und übertragen. Die Verbindung wird wieder geschlossen. Auch in diesem Projekt muss der erste Buffer-Eintrag einen eindeutigen Eintrag enthalten. In diesem Fall muss 0xBB (Modus B) im ersten Buffer-Eintrag stehen. Der Rest des Buffers besteht aus Bilddaten.
