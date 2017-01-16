#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import re

def refer_module_alias(st):
    if ' as ' in st:
        return st.split()[0]
    return st

class InfoWriter(object):
    def __init__(self, readerName, writerName, excludes=None):
        self.excludes = excludes
        try:
            self.writer = open(writerName, 'a')
            self.reader = open(readerName, 'r')
        except IOError as ex:
            print "failed to read or write file"
            raise ex

    def extract_modules(self):
        modnames = []
        for line in self.reader.readlines():
            line = line.strip()
            if 'from ' == line[0:5]:	# from some_module import name_list|*;; name_list ::= name, name_list ::= name, name_list
                module_name = line.split()[1]
                modnames.append(module_name)
            elif 'import ' == line[0:7]:	#import module_list;; module_list ::= module_name[ as alias_name], module_list ::= module_name, module_list
                module_name = line.split(None, 1)[1]
                if ',' in module_name:
                    modnamesep = re.compile(r',\s*')
                    module_seq = re.split(modnamesep, module_name)
                    modnames.extend(map(refer_module_alias, module_seq))
                else:
                    modnames.append(refer_module_alias(line.split()[1]))
        self.reader.close()
        return modnames

    def get_unkown_modules(self):
        unkownmod = []
        modnameset = set(self.extract_modules())
        for module_name in modnameset:
            if self.excludes and module_name in self.excludes:
                continue
            try:
                exec 'import %s' % module_name
            except ImportError:
                #TODO search the module with pip, get info about unkown modules
                unkownmod.append(module_name)
        return unkownmod

    def render_report(self):
        strls =[]
        if self.writer.tell() != 0:
            strls.append('\n')
        strls.append('{\n"FileName":\n\t')
        strls.append('"%s",\n' % self.reader.name)

        unkown_modules = self.get_unkown_modules()
        if unkown_modules:
            strls.append('"unkown modules":\n\t[\n\t')
            unkownmods = ['"%s"' % s for s in unkown_modules]
            strls.append(',\n\t'.join(unkownmods))
            strls.append('\n\t]\n}\n')
            self.writer.write(''.join(strls))

    def close(self):
        self.writer.close()

if __name__ == '__main__':
    report = 'modules_report.txt'
    if os.path.exists(report):
        os.unlink(report)
    PROJDIR = '/home/e550c/projects/weiboclient'
    bsnls = [f.split('.')[0] for f in os.listdir(PROJDIR) if f.endswith('.py')]
    # print bsnls
    for fn in [os.path.join(PROJDIR, i) for i in os.listdir(PROJDIR) if i.endswith('.py')]:
        iw = InfoWriter(fn, report, excludes=bsnls)
        iw.render_report()
        iw.close()
