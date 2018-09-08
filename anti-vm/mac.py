from uuid import getnode

# some MAC OUIs were taken from pafish (awesome tool)
# https://github.com/a0rtega/pafish/blob/master/pafish/vmware.c
virtual_macs = [
        #Vmware
        "00:05:69", "00:0C:29", "00:1C:14", "00:50:56",
        #VBox
        "08:00:27",
        #Parallels
        "00:1C:42",
        #Xen
        "00:16.3E",
        #KVM
        "00:A0:B1",
        #VirtualPC
        "00:03:FF"
]

mac = getnode()
b1 = (mac >> 0x28)
b2 = ((mac >> 0x20) & 0xff)
b3 = ((mac >> 0x18) & 0xff)
str_mac = "%02X:%02X:%02X" % (b1,b2,b3)

print "MAC = %s" % str_mac
for vm in virtual_macs:
    if str_mac == vm:
        print "OMG! IS A VM!"
        quit(-1)

print "Not a VM! Let's do this :B"

