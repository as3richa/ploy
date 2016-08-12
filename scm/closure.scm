(define map (lambda (proc li)
              (or
               (and (empty? li) empty)
               (cons (proc (first li)) (map proc (rest li))))))

(define adder (lambda (n) (lambda (x) (+ n x))))

((adder 5) 10)
(map (adder 100) (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 empty))))))
