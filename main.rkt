#lang racket

(require ffi/unsafe
         ffi/unsafe/define)


(define-ffi-definer define-shell (ffi-lib "racketglshell"))

(define-cstruct _RenderState ([red _float]
                             [green _float]
                             [blue _float]))

(define-shell shell_open (_fun _string _int _int -> _void))
(define-shell shell_is_open (_fun -> _stdbool))
(define-shell shell_update (_fun _RenderState-pointer -> _void))
(define-shell shell_close (_fun -> _void))


(define i 0.0)

(define (main-loop)
  (when (shell_is_open)
    (set! i (let ([new-i (+ i 0.01)]) (if (> new-i 1.0) 0.0 new-i)))
    (shell_update (make-RenderState 0.0 i 0.0))
    (sleep (/ 1 60))
    (main-loop)))

(define (run-game)
  (shell_open "Hello World" 640 480)
  (main-loop))