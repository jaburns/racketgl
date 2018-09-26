#lang racket

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-shell (ffi-lib "racketglshell"))

(define-shell add_floats (_fun _float _float -> _float))
