#lang racket

; public static int calculatePlus(int a, int b) {
;    return a + b;
; }

(define (calculatePlus a b)
  (+ a b))

; public static int calculateSomething(Function<Integer, Integer> f, int a, int b) {
;    return f.apply(a, b);
; }
(define (calculateSomething fun a b)
  (fun a b))

(define (buildAdder x) (lambda (a) (+ a x)))
(define add3 (buildAdder 3))
(define add7 (buildAdder 7))
; (define (add3 b) (+ 3 b))
; (define (add7 b) (+ 7 b))

; special higher order functions that apply to lists of data
;  map - repeatedly apply a function to the values in a list creating a new list of results
(map add7 '(1 2 3 4 5))
(map (lambda (a b c) (+ a b c)) '(1 2 3 4 5) '(7 7 7 7 7) '(1 1 1 1 1))

; filter - filters a list with a function elements must "pass" in order to stay in the list
; ArrayList<Integer> nums = new ArrayList<>(); // load nums up with 7 through 13
; Iterator<Integer> it = nums.iterator();
; while (it.hasNext()) {
;  if (it.next() >= 10) {
;     it.remove();
;  }
; }
(filter (lambda (a) (< a 10)) '(7 8 9 10 11 12 13))
(> (length (filter (lambda (a) (< a 10)) '(7 8 9 10 11 12 13))) 2)

; fold (better known as "reduce") - reduces a list to a single number using a function
(foldl + 0 '(1 2 3 4 5 6 7 8 9 10))  

