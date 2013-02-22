#!/usr/bin/python
"""
This script asks cdash to give it a summary of all of the failing tests
on the nightly expected section. It presents the tests ranked by the number
of failing machines. From this view you can more easily see what is in
the greatest need of fixing.
"""

import urllib
url = 'http://open.cdash.org/api/?method=build&task=sitetestfailures&project=VTK&group=Nightly%20Expected'
page = urllib.urlopen(url)
data = page.readlines()
if len(data[0]) == 2: #"[]"
  print "Cdash returned nothing useful, please try again later."
  raise SystemExit

submissions = eval(data[0])
tfails = dict()
print "-"*20, "ANALYZING", "-"*20
for skey in submissions.keys():
  submission = submissions[skey]
  bname = submission['buildname']
  bfails = submission['tests']
  if len(bfails) > 100:
    print "WARNING IGNORING ", bname, len(bfails)
    continue
  print bname, ",", len(bfails)
  for tnum in range(0, len(bfails)):
    test = bfails[tnum]
    tname = test['name']
    if not tname in tfails:
       tfails[tname] = list()
    tfails[tname].append(bname)

print "-"*20, "REPORT", "-"*20
print len(tfails)," FAILURES"
failcounts = map(lambda x: (x,len(tfails[x])), tfails.keys())
sortedfails = sorted(failcounts, key=lambda fail: fail[1])
for test in sortedfails:
  tname = test[0]
  print tname, ",", len(tfails[tname]), ",", tfails[tname]
