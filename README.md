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
      
* insert - įterpia reikšmę į pasirinktą vietą

      //insert()
      template <class T>
      void Vec<T>::insert(const_iterator it, const_reference value)
      {
          int temp = 0;
          for (auto i = this->begin(); i != it; i++)
          {
              temp++;
          }
          //from grow() function
          size_type new_size = this->size()+1;
          iterator new_data_ = alloc.allocate(new_size);
          iterator new_avail = uninitialized_copy(data_, avail+1, new_data_);
          for (size_t i=0; i<temp; i++)
          {
              new_data_[i] = data_[i];
          }
          new_data_[temp] = value;
          for (size_t i=temp+1; i!=new_size; i++)
          {
              new_data_[i] = data_[i-1];
          }
          uncreate();
          //from grow() function
          data_ = new_data_;
          avail = new_avail;
          limit = data_ + new_size;

      }
      
* resize - pakeičia konteinerio dydį ir į laisvas vietas įrašo reikšmę

      //resize()
      template <class T>
      void Vec<T>::resize(int it)
      {
          int count = 0;
          if (it < this->size())
          {
              for (size_t i=it; i!=this->size(); i++)
              {
                  this->data_[i] = 0;
                  count ++;
              }
              avail -= count;
          }
          else
          {
              int sz = this->size();
              this->avail += it - this->size();
              for (size_t i=sz; i!=it; i++)
              {
                  this->data_[i] = 0;
              }
          }
      }
      
* erase - ištrina elementą pasiriktoje konteinerio vietoje

      //erase()
      template<class T>
      void Vec<T>::erase(const_iterator it)
      {
          if (it < data_ || it > avail)
              throw out_of_range{ "erase()" };
          int temp = 0;
          for (auto i = begin(); i < it; i++)
          {
              temp++;
          }
          for (temp; temp < size(); temp++)
          {
              data_[temp] = data_[temp + 1];
          }
          avail--;
      }
      
* swap - apkeičia dviejų konteinerių duomenis tarpusavy

      //swap()
      template <class T>
      void Vec<T>::swap(Vec<T>& l) noexcept
      {
          iterator temp_data_ = this->data_;
          iterator temp_avail = this->avail;
          iterator temp_limit = this->limit;
          this->data_ = l.data_;
          this->avail = l.avail;
          this->limit = l.limit;
          l.data_ = temp_data_;
          l.avail = temp_avail;
          l.limit = temp_limit;
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
