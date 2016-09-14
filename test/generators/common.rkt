#lang racket

(define (bits i n)
  (if (zero? n)
      empty
      (cons (odd? i) (bits (quotient i 2) (sub1 n)))))

(define (bit-lists n)
  (if (zero? n)
      (list empty)
      (append-map (lambda (r) (list (cons #f r) (cons #t r))) (bit-lists (sub1 n)))))

(define ns (make-base-namespace))

(define (generate-slug-testcase id slug param-lists)
  (let [(definition `(define ,id ,slug))]
    (eval definition ns)
    (let [(arity (eval `(procedure-arity ,id) ns))]
      (printf "~a\n" definition)
      (for [(param-list param-lists)]
        (let* [
               (invocation `(,id ,@param-list))
               (result (eval invocation ns))]
          (printf "~a ; ~a\n" invocation result)
          (fprintf (current-error-port) "~a\n" result))))))

(provide (all-defined-out))