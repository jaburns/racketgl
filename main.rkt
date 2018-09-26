#lang racket

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-shell (ffi-lib "racketglshell"))

#|
(define-cstruct _ShellState ([sdl_window _pointer]
                             [sdl_context _pointer]
                             [window_width _int]
                             [window_height _int]))
(define-shell shell_init (_fun _string _int _int -> _ShellState))
|#

(define-cstruct _FloatPair ([first _float]
                            [second _float]))
(define-shell add_floats (_fun _FloatPair -> _float))
