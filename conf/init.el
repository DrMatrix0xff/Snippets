(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(auto-insert-mode t)
 '(auto-save-default nil)
 '(blink-cursor-mode nil)
 '(c-basic-offset 4)
 '(column-number-mode t)
 '(inhibit-startup-screen t)
 '(initial-scratch-message nil)
 '(js-indent-level 2)
 '(make-backup-files nil)
 '(python-indent-offset 4)
 '(scheme-program-name "scheme")
 '(scroll-bar-mode nil)
 '(show-paren-mode t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

;; (add-to-list 'load-path "~/.emacs.d")
;; use arrow keys instead
(global-unset-key (kbd "C-f"))
(global-unset-key (kbd "C-b"))

(global-set-key (kbd "C-b") 'scroll-down-command)
(global-set-key (kbd "C-f") 'scroll-up-command)

(global-set-key (kbd "C-x ,") 'set-mark-command)
(global-set-key (kbd "C-x c") 'delete-region)
(global-set-key (kbd "RET") 'newline-and-indent)
(global-set-key (kbd "C-j") 'newline)

(fset 'yes-or-no-p 'y-or-n-p)

(eval-after-load 'autoinsert
  '(define-auto-insert '(c-mode . "C skeleton")
     '("Description: "
       "/*" > \n
       "* Module name: " (file-name-nondirectory (buffer-file-name)) > \n
       "* Create on " (format-time-string "%a, %b %d %Y.") > \n
       "*" > \n
       "*/" > \n \n
       > _ \n
       )))

(eval-after-load 'autoinsert
  '(define-auto-insert '(c++-mode . "CPP skeleton")
     '("Description: "
       "/*" > \n
       "* Module name: "  (file-name-nondirectory (buffer-file-name)) > \n
       "* Create on " (format-time-string "%a, %b %d %Y.") > \n
       "*" > \n
       "*/" > \n \n
       > _ \n
       )))

(eval-after-load 'autoinsert
  '(define-auto-insert '(java-mode . "Java skeleton")
     '("Description: "
       "/*" > \n
       "* Module name: "  (file-name-nondirectory (buffer-file-name)) > \n
       "* Create on " (format-time-string "%a, %b %d %Y.") > \n
       "*" > \n
       "*/" > \n \n
       > _ \n
       )))

(eval-after-load 'autoinsert
  '(define-auto-insert '(javascript-mode . "js skeleton")
     '("Description: "
       "/*" > \n
       "* Module name: " (file-name-nondirectory (buffer-file-name)) > \n
       "* Create on " (format-time-string "%a, %b %d %Y.") > \n
       "*" > \n
       "*/" > \n \n
       > _ \n
       )))

(eval-after-load 'autoinsert
  '(define-auto-insert '(python-mode . "Python skeleton")
     '("Description: "
       "#!/usr/bin/env python" \n
       "# -*- coding: utf-8 -*-" \n \n
       "# Create on " (format-time-string "%a, %b %d %Y.") > \n \n
       _ \n)))

(eval-after-load 'autoinsert
  '(define-auto-insert '(html-mode . "HTML skeleton")
     '("Please insert your title: "
       "<!DOCTYPE html>" \n
       "<html>" \n
       "<head>" > \n
       "<meta charset=utf-8>" > \n
       "<title>" str "</title>" > \n
       "</head>" > \n
       "<body>" > \n
       > _ \n
       "</body>" > \n
       "</html>" > \n \n)))

(eval-after-load 'autoinsert
  '(define-auto-insert '(sh-mode . "Shell skeleton")
     '("Description: "
       "#!/bin/sh" \n
       "# Create on " (format-time-string "%a, %b %d %Y.") > \n \n
       _ \n)))

(server-start)
(put 'dired-find-alternate-file 'disabled nil)
