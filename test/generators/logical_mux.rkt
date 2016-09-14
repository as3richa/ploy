#lang racket

(require "common.rkt")

(define mux2slug '(lambda (a b x)
                    (or (and (not x) a) (and x b))))

(define mux4slug '(lambda (a b c d x y)
                    (or
                     (and (not x) (mux2 a b y))
                     (mux2 c d y))))

(define mux8slug '(lambda (a b c d e f g h x y z)
                    (or
                      (and (not x) (mux4 a b c d y z))
                      (mux4 e f g h y z))))

(define mux16slug '(lambda (a b c d e f g h i j k l m n o p w x y z)
                     (or
                       (and (not w) (mux8 a b c d e f g h x y z))
                       (mux8 i j k l m n o p x y z))))


(generate-slug-testcase 'mux2 mux2slug (bit-lists 3))
(generate-slug-testcase 'mux4 mux4slug (bit-lists 6))
(generate-slug-testcase 'mux8 mux8slug (bit-lists 11))
(generate-slug-testcase 'mux16 mux16slug (take (bit-lists 20) 10000))
