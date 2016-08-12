(define xor (lambda (x y)
              (or
               (and x (not y))
               (and y (not x )))))

(define mux (lambda (x y m)
              (or
               (and x (not m))
               (and y m))))

(xor #f #f)
(xor #f #t)
(xor #t #f)
(xor #t #t)

(mux #f #f #f)
(mux #f #f #t)
(mux #f #t #f)
(mux #f #t #t)
(mux #t #f #f)
(mux #t #f #t)
(mux #t #t #f)
(mux #t #t #t)
