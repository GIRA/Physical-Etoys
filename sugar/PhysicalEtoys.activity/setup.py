#!/usr/bin/env python
try:
    from sugar.activity import bundlebuilder
    bundlebuilder.start()
except ImportError:
    import os
    os.system("find ./ | sed 's,^./,PhysicalEtoys.activity/,g' > MANIFEST")
    os.system('rm PhysicalEtoys.xo')
    os.chdir('..')
    os.system('zip -r PhysicalEtoys.xo PhysicalEtoys.activity')
    os.system('mv PhysicalEtoys.xo ./PhysicalEtoys.activity')
    os.chdir('PhysicalEtoys.activity')
