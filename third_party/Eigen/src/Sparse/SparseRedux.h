
#ifndef EIGEN_SPARSEREDUX_H
#define EIGEN_SPARSEREDUX_H

template<typename Derived>
typename internal::traits<Derived>::Scalar
SparseMatrixBase<Derived>::sum() const
{
  eigen_assert(rows()>0 && cols()>0 && "you are using a non initialized matrix");
  Scalar res = 0;
  for (Index j=0; j<outerSize(); ++j)
    for (typename Derived::InnerIterator iter(derived(),j); iter; ++iter)
      res += iter.value();
  return res;
}

template<typename _Scalar, int _Options, typename _Index>
typename internal::traits<SparseMatrix<_Scalar,_Options,_Index> >::Scalar
SparseMatrix<_Scalar,_Options,_Index>::sum() const
{
  eigen_assert(rows()>0 && cols()>0 && "you are using a non initialized matrix");
  return Matrix<Scalar,1,Dynamic>::Map(&m_data.value(0), m_data.size()).sum();
}

template<typename _Scalar, int _Options, typename _Index>
typename internal::traits<SparseVector<_Scalar,_Options, _Index> >::Scalar
SparseVector<_Scalar,_Options,_Index>::sum() const
{
  eigen_assert(rows()>0 && cols()>0 && "you are using a non initialized matrix");
  return Matrix<Scalar,1,Dynamic>::Map(&m_data.value(0), m_data.size()).sum();
}

#endif // EIGEN_SPARSEREDUX_H
