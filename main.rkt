#lang racket

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-shell (ffi-lib "racketglshell"))

(define-cstruct _RenderState ([red _float]
                             [green _float]
                             [blue _float]))

(define-shell shell_open (_fun _string _int _int -> _void))
(define-shell shell_update (_fun _RenderState-pointer -> _void))
(define-shell shell_close (_fun -> _void))

(shell_open "Hello World" 640 480)

(for ([i (in-range 0.0 1.0 0.01)])
    (shell_update (make-RenderState 0.0 i 0.0))
    (sleep (/ 1 60)))

(shell_close)