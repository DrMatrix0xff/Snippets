#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import logging

logger = logging.getLogger('main')
logger.setLevel(logging.INFO)
#handler = logging.FileHandler('logger.log')
handler = logging.StreamHandler(stream=sys.stdout)
formatter = logging.Formatter("[ %(levelname)s %(asctime)s ] -- %(message)s", datefmt="%y-%m-%d %H:%M:%S")
handler.setFormatter(formatter)
logger.addHandler(handler)

def main():
    logger.info('hello world')
    logger.warn('something not bad enough')
    logger.error('something really bad')
    logger.fatal('something extremely bad')

if __name__ == '__main__':
    main()
