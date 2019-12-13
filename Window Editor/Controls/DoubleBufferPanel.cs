using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowEditor
{
    public class DoubleBufferPanel : Panel
    {
        public DoubleBufferPanel()
        {
            this.DoubleBuffered = true;
        }
    }
}
