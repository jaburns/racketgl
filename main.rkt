#lang racket

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-shell (ffi-lib "racketglshell"))

(define-cstruct _FloatPair ([first _float]
                            [second _float]))

(define-shell add_floats (_fun _FloatPair -> _float))