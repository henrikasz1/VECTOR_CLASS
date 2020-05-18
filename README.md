# VECTOR_CLASS
creating vector class c++
---------------
5 sukurtų funkcijų aprašai
---------------
* shrink_to_fit - sumažina konteinerio capacity() iki jo dydžio (size())    (  capacity() = size()  )

      //shrink_to_fit()
      template <class T>
      void Vec<T>::shrink_to_fit() const
      {
          limit = avail;
      }


---------------
Spartos analizė
---------------
std::vector VS vector class (using push_back() to insert a certain amount of values to vector)

|   Container   |  10K |  100K  |  1MLN   |  10MLN   |  100MLN  |
|---------------|------|--------|---------|----------|----------|
|  class_vector |  0s  | 0.004s | 0.038s  |  0.338s  |  2.998s  |
|   std::vector |  0s  | 0.005s | 0.039s  |  0.337s  |  3.013s  |


*Išvada: abiejų konteinerių laikai yra labai panašūs
