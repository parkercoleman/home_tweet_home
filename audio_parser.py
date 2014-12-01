#All of the non-trivial parts of this program (the frequency extraction) is code from Justin Peel
#At http://stackoverflow.com/questions/2648151/python-frequency-detection Thanks a bunch!


import pyaudio
import wave
import numpy as np
from notes import note_map
import logging
import time

logging.basicConfig(level=logging.DEBUG)
LOG = logging.getLogger()

chunk = 2048
file_name = 'hum.wav'
wf = wave.open(file_name, 'rb')
swidth = wf.getsampwidth()
RATE = wf.getframerate()
# use a Blackman window
window = np.blackman(chunk)

def extract_tone_from_chunk(data):
    #again, to reiterate, not my code.
    # Obtained from http://stackoverflow.com/questions/2648151/python-frequency-detection

    # unpack the data and times by the hamming window
    indata = np.array(wave.struct.unpack("%dh"%(len(data)/swidth),\
                                         data))*window
    # Take the fft and square each value
    fftData=abs(np.fft.rfft(indata))**2
    # find the maximum
    which = fftData[1:].argmax() + 1
    # use quadratic interpolation around the max
    if which != len(fftData)-1:
        y0,y1,y2 = np.log(fftData[which-1:which+2:])
        x1 = (y2 - y0) * .5 / (2 * y1 - y2 - y0)
        # find the frequency and output it
        thefreq = (which+x1)*RATE/chunk #name your god and bleed thefreq
        LOG.info("Chunk freq is %f Hz." % (thefreq))
        return thefreq
    else:
        thefreq = which*RATE/chunk
        return thefreq
        LOG.info("Chunk freq is %f Hz." % (thefreq))


def auto_tune(raw_freq):
    min_diff = 100000
    note = None
    freq = None
    for name, f in note_map.items():
        d = abs(f-raw_freq)
        if d < min_diff:
            min_diff = d
            freq = f
            note = name

    LOG.info("auto tuning %s to %s: %s " % (raw_freq, freq, note))
    return freq


def simplify(milli_per_note, frequencies):
    s_frequencies = []
    s_millis = []
    cur_val = frequencies[0]
    milli_count = milli_per_note

    for f in frequencies:
        if f != cur_val:
            if cur_val is not None:
                s_frequencies.append(cur_val)
                s_millis.append(milli_count)
            cur_val = f
            milli_count = milli_per_note
        else:
            milli_count += milli_per_note

    return s_frequencies, s_millis


def format_arduino_array(array_name, vals):
    s = "PROGMEM short %s[] = {" % array_name
    for f in vals[:-1]:
        s += (str(int(round(f))) + ", ")

    s += str(int(round(vals[-1]))) + "};"
    return s


def main():
    # open stream
    p = pyaudio.PyAudio()
    frequencies = []

    # read some data
    data = wf.readframes(chunk)
    while len(data) == chunk * swidth:
        frequencies.append(auto_tune(extract_tone_from_chunk(data)))
        data = wf.readframes(chunk)
    wf.close()
    p.terminate()

    milli_per_sample = int(round((chunk/float(RATE)) * 1000))
    LOG.info("%s milliseconds per sample " % milli_per_sample)

    s_frequencies, milli_per_note = simplify(milli_per_sample, frequencies)
    LOG.info("%s simplified notes and %s millisecond per note entries (These better match!)" %
             (len(s_frequencies), len(milli_per_note)))

    time.sleep(1)
    print format_arduino_array("maria_freqs", s_frequencies)
    print format_arduino_array("maria_millis", milli_per_note)

if __name__ == '__main__':
    main()