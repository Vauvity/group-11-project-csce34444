import wave
import sys

def trim_wav(filename, trim_seconds=0.5):
    try:
        with wave.open(filename, 'rb') as w_in:
            nchannels = w_in.getnchannels()
            sampwidth = w_in.getsampwidth()
            framerate = w_in.getframerate()
            nframes = w_in.getnframes()
            
            frames_to_keep = nframes - int(trim_seconds * framerate)
            if frames_to_keep <= 0:
                print(f"File {filename} is too short to trim {trim_seconds}s")
                return
                
            frames = w_in.readframes(frames_to_keep)
            
        with wave.open(filename, 'wb') as w_out:
            w_out.setnchannels(nchannels)
            w_out.setsampwidth(sampwidth)
            w_out.setframerate(framerate)
            w_out.writeframes(frames)
            
        print(f"Successfully trimmed {trim_seconds}s from {filename}")
    except Exception as e:
        print(f"Error trimming {filename}: {e}")

trim_wav('SpaceCasinoUI/assets/audio/roulette_spin.wav')
trim_wav('SpaceCasinoUI/assets/audio/slotmachine.wav')
