/**
 * Authors: Rick Vogel, Philipp Thomasberger
 * Created: 24.09.2015
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Serial
{    
    public delegate void MouseTrackAddEventHandler(object sender, MouseTrackAddEventArgs e);
    public delegate void MouseTrackDeleteEventHandler(object sender, MouseTrackDeleteEventArgs e);

    public partial class RemoteDisplay : UserControl
    {
        private
            // stores points of the mouse track
            LinkedList<Point> mouseTrack = new LinkedList<Point>();
        private
            // defines the length of the mouse track
            int mouseTrackLength = 100;
        public
            event MouseTrackAddEventHandler MouseTrackAddEvent;
        public
            event MouseTrackDeleteEventHandler MouseTrackDeleteEvent;

        // Invoke the Changed event; called whenever list changes
        protected virtual void OnMouseTrackAdd(MouseTrackAddEventArgs e)
        {
            if (MouseTrackAddEvent != null)
                MouseTrackAddEvent(this, e);
        }

        // Invoke the Changed event; called whenever list changes
        protected virtual void OnMouseTrackDelete(MouseTrackDeleteEventArgs e)
        {
            if (MouseTrackDeleteEvent != null)
                MouseTrackDeleteEvent(this, e);
        }

        public RemoteDisplay()
        {
            InitializeComponent();
        }

        private void RemoteDisplay_MouseMove(object sender, MouseEventArgs e)
        {
            if (mouseTrack.Count == 0 || !mouseTrack.First.Value.Equals(e.Location))
            {
                mouseTrack.AddFirst(e.Location);
                CreateGraphics().DrawRectangle(new Pen(Color.Black), new Rectangle(mouseTrack.First.Value, new Size(1, 1)));
                OnMouseTrackAdd(new MouseTrackAddEventArgs(e.Location));
            }
            if (mouseTrack.Count > mouseTrackLength)
            {
                CreateGraphics().DrawRectangle(new Pen(BackColor), new Rectangle(mouseTrack.Last.Value, new Size(1, 1)));
                Point last = mouseTrack.Last.Value;
                mouseTrack.RemoveLast();
                OnMouseTrackDelete(new MouseTrackDeleteEventArgs(last));
            }
        }
    }

    public class MouseTrackEventArgs : EventArgs
    {
        private
            Point location;
        protected
            bool on;
        public Point Location
        {
            get
            {
                return location;
            }
        }

        public bool On
        {
            get
            {
                return on;
            }
        }

        public MouseTrackEventArgs(Point location)
        {
            this.location = location;
        }
    }

    public class MouseTrackAddEventArgs : MouseTrackEventArgs
    {
        public MouseTrackAddEventArgs(Point location) : base(location)
        {
            on = true;
        }
    }

    public class MouseTrackDeleteEventArgs : MouseTrackEventArgs
    {
        public MouseTrackDeleteEventArgs(Point location) : base(location)
        {
            on = false;
        }
    }

}
