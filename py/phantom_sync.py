#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Created on Monday, 31 August 2015.

import time
import logging
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait

logging.basicConfig(
    filename="waitjs.log",
    level=logging.INFO,
    format='[ %(levelname)s ] %(threadName)s: %(asctime)s; %(message)s',
    datefmt='%m/%d/%Y %H:%M:%S'
)
brz = webdriver.PhantomJS()
brz.get('race_cond.html')
print 'alreay access...'

logging.info("wait executing js...")
WebDriverWait(brz, timeout=10).until(lambda d: d.find_element_by_tag_name("p"))
logging.info("finish...")
# brz.implicitly_wait(2)
el = brz.find_element_by_tag_name("p")

print el.text

print "page source: %s" % brz.page_source.encode('utf-8')
print 'sleeping for 5 seconds...'
time.sleep(5)
brz.quit()
