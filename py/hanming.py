import pylab as pl
import scipy.signal as signal
pl.figure(figsize=(6,2))
pl.plot(signal.hanning(512))
pl.show()