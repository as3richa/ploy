(define empty? (lambda (v) (eq? v empty)))

(define map (lambda (proc lst)
              (if (empty? lst)
                empty
                (cons (proc (first lst)) (map proc (rest lst))))))
