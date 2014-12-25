

b = open('avemaria_txt/beats.txt', 'r').readlines()
n = open('avemaria_txt/notes.txt', 'r').readlines()

print b
print n

def format_arduino_array(array_name, vals):
    s = "PROGMEM short %s[] = {" % array_name
    for f in vals[:-1]:
        s += (str(int(round(f))) + ", ")

    s += str(int(round(vals[-1]))) + "};"
    return s


i = 0
b_sub = []
for i in range(0, len(b)-1):
    x = (int(b[i+1]) - int(b[i])) * 3
    if x < 0:
        print "fart"
    b_sub.append(x)

print format_arduino_array("maria_millis", b_sub)

notes = []
volume = []
for nline in n:
    l = nline.split(" ")
    notes.append(int(l[1]))
    volume.append(round(int(l[2]) / 10))

print format_arduino_array("maria_freqs", notes)
print format_arduino_array("maria_volume", volume)

print len(b_sub)
print len(notes)
print len(volume)