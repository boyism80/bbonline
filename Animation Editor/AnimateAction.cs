using System.Collections.Generic;
using System.IO;

namespace AnimationEditor
{
    public class AnimateAction
    {
        private int _current;

        public List<AnimateFrame> animateFrames { get; private set; }
        public bool isLoop { get; set; }
        public string name { get; set; }
        public float duration
        {
            get
            {
                var ret = 0.0f;
                foreach(var frame in this.animateFrames)
                    ret += frame.duration;

                return ret;
            }
            set
            {
                var eachDuration = value / this.animateFrames.Count;
                foreach(var frame in this.animateFrames)
                    frame.duration = eachDuration;
            }
        }

        public AnimateFrame currentFrame
        {
            get
            {
                if(this._current > this.animateFrames.Count)
                    return null;

                return this.animateFrames[this._current];
            }
        }
        
        public AnimateAction(string name, bool isLoop = false)
        {
            this.animateFrames = new List<AnimateFrame>();
            this.name = name;
            this.isLoop = isLoop;
        }

        public void reset()
        {
            this._current = 0;
        }

        public bool next()
        {
            this._current++;
            if(this._current > this.animateFrames.Count - 1)
            {
                if(this.isLoop)
                    this._current = 0;
                else
                    return false;
            }

            return true;
        }

        public void save(BinaryWriter writer)
        {
            writer.Write(this.name);
            writer.Write(this.isLoop);

            writer.Write(this.animateFrames.Count);
            foreach(var frame in this.animateFrames)
                frame.save(writer);
        }

        public static AnimateAction load(BinaryReader reader)
        {
            var name = reader.ReadString();
            var isLoop = reader.ReadBoolean();
            var animateAction = new AnimateAction(name, isLoop);

            var count = reader.ReadInt32();
            for(var i = 0; i < count; i++)
                animateAction.animateFrames.Add(AnimateFrame.load(reader));

            return animateAction;
        }
    }
}