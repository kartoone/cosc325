#lang racket
(define pi 3.14159)
(define pi_p1 (+ pi 1))
(define test_data '(1 2 3 4 5 6 7 8 9 10))

(foldl + 0 test_data)
; total = 0
; for num in test_data:
;   total += num

(foldl * 1 test_data)
; product = 1
; for num in test_data:
;    product *= num

; thresh is essentially a local constant
; this function only calculates correct value for small numbers
; otherwise it returns 0
(define (smallsum2 a b)
  (define thresh 100)
  (if (< (+ a b) thresh) (+ a b) 0))



(define (factorial x)
  (if (<= x 1)
      1
      (* x (factorial (- x 1)))))

(define (doit f a)
  (f a))

(map factorial '(5 9 12))

;(require net/http-easy)
;(define apiUrl "https://api.open-meteo.com/v1/forecast?latitude=33.5&longitude=-86.8&daily=temperature_2m_max,temperature_2m_min&temperature_unit=fahrenheit&timezone=auto")
