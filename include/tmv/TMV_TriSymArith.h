///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// The Template Matrix/Vector Library for C++ was created by Mike Jarvis     //
// Copyright (C) 1998 - 2016                                                 //
// All rights reserved                                                       //
//                                                                           //
// The project is hosted at https://code.google.com/p/tmv-cpp/               //
// where you can find the current version and current documention.           //
//                                                                           //
// For concerns or problems with the software, Mike may be contacted at      //
// mike_jarvis17 [at] gmail.                                                 //
//                                                                           //
// This software is licensed under a FreeBSD license.  The file              //
// TMV_LICENSE should have bee included with this distribution.              //
// It not, you can get a copy from https://code.google.com/p/tmv-cpp/.       //
//                                                                           //
// Essentially, you can use this software however you want provided that     //
// you include the TMV_LICENSE file in any distribution that uses it.        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#ifndef TMV_TriSymArith_H
#define TMV_TriSymArith_H

#define CT std::complex<T>

namespace tmv {

    //
    // TriMatrix + SymMatrix
    //

    template <typename T, typename T1, typename T2>
    class SumUS : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline SumUS(
            T _x1, const GenUpperTriMatrix<T1>& _m1,
            T _x2, const GenSymMatrix<T2>& _m2) :
            x1(_x1),m1(_m1),x2(_x2),m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m1.size(); }
        inline ptrdiff_t rowsize() const { return m1.size(); }
        inline T getX1() const { return x1; }
        inline const GenUpperTriMatrix<T1>& getM1() const { return m1; }
        inline T getX2() const { return x2; }
        inline const GenSymMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                UpperTriMatrix<T1> m1x = m1;
                MultXM(x2,m0=m2);
                AddMM(x1,m1x,m0);
            } else {
                MultXM(x2,m0=m2);
                AddMM(x1,m1,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                UpperTriMatrix<T1> m1x = m1;
                MultXM(x2,m0=m2);
                AddMM(x1,m1x,m0);
            } else {
                MultXM(x2,m0=m2);
                AddMM(x1,m1,m0);
            }
        }
    private:
        const T x1;
        const GenUpperTriMatrix<T1>& m1;
        const T x2;
        const GenSymMatrix<T2>& m2;
    };

    template <typename T, typename T1, typename T2>
    class SumLS : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline SumLS(
            T _x1, const GenLowerTriMatrix<T1>& _m1,
            T _x2, const GenSymMatrix<T2>& _m2) :
            x1(_x1),m1(_m1),x2(_x2),m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m1.size(); }
        inline ptrdiff_t rowsize() const { return m1.size(); }
        inline T getX1() const { return x1; }
        inline const GenLowerTriMatrix<T1>& getM1() const { return m1; }
        inline T getX2() const { return x2; }
        inline const GenSymMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                LowerTriMatrix<T1> m1x = m1;
                MultXM(x2,m0=m2);
                AddMM(x1,m1x,m0);
            } else {
                MultXM(x2,m0=m2);
                AddMM(x1,m1,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                LowerTriMatrix<T1> m1x = m1;
                MultXM(x2,m0=m2);
                AddMM(x1,m1x,m0);
            } else {
                MultXM(x2,m0=m2);
                AddMM(x1,m1,m0);
            }
        }
    private:
        const T x1;
        const GenLowerTriMatrix<T1>& m1;
        const T x2;
        const GenSymMatrix<T2>& m2;
    };

#define SUMMM SumUS
#define GENMATRIX1 GenUpperTriMatrix
#define GENMATRIX2 GenSymMatrix
#define PRODXM1 ProdXU
#define PRODXM2 ProdXS
#include "tmv/TMV_AuxSumMM.h"
#include "tmv/TMV_AuxSumMMb.h"
#undef SUMMM
#undef GENMATRIX1
#undef PRODXM1
#define SUMMM SumLS
#define GENMATRIX1 GenLowerTriMatrix
#define PRODXM1 ProdXL
#include "tmv/TMV_AuxSumMM.h"
#include "tmv/TMV_AuxSumMMb.h"
#undef SUMMM
#undef GENMATRIX1
#undef GENMATRIX2
#undef PRODXM1
#undef PRODXM2

    //
    // TriMatrix * SymMatrix
    //

    template <typename T, typename T1, typename T2>
    class ProdUS : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline ProdUS(
            T _x, const GenUpperTriMatrix<T1>& _m1,
            const GenSymMatrix<T2>& _m2) :
            x(_x), m1(_m1), m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m2.size(); }
        inline ptrdiff_t rowsize() const { return m2.size(); }
        inline T getX() const { return x; }
        inline const GenUpperTriMatrix<T1>& getM1() const { return m1; }
        inline const GenSymMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                UpperTriMatrix<T1> m1x = m1;
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1x,m0,m0);
            } else {
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1,m0,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                UpperTriMatrix<T1> m1x = m1;
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1x,m0,m0);
            } else {
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1,m0,m0);
            }
        }
    protected:
        T x;
        const GenUpperTriMatrix<T1>& m1;
        const GenSymMatrix<T2>& m2;
    };

    template <typename T, typename T1, typename T2>
    class ProdSU : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline ProdSU(
            T _x, const GenSymMatrix<T1>& _m1,
            const GenUpperTriMatrix<T2>& _m2) :
            x(_x), m1(_m1), m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m1.size(); }
        inline ptrdiff_t rowsize() const { return m1.size(); }
        inline T getX() const { return x; }
        inline const GenSymMatrix<T1>& getM1() const { return m1; }
        inline const GenUpperTriMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m2)) {
                UpperTriMatrix<T2> m2x = m2;
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2x,m0);
            } else {
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m2)) {
                UpperTriMatrix<T2> m2x = m2;
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2x,m0);
            } else {
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2,m0);
            }
        }
    protected:
        T x;
        const GenSymMatrix<T1>& m1;
        const GenUpperTriMatrix<T2>& m2;
    };

    template <typename T, typename T1, typename T2>
    class ProdLS : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline ProdLS(
            T _x, const GenLowerTriMatrix<T1>& _m1,
            const GenSymMatrix<T2>& _m2) :
            x(_x), m1(_m1), m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m2.size(); }
        inline ptrdiff_t rowsize() const { return m2.size(); }
        inline T getX() const { return x; }
        inline const GenLowerTriMatrix<T1>& getM1() const { return m1; }
        inline const GenSymMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                LowerTriMatrix<T1> m1x = m1;
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1x,m0,m0);
            } else {
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1,m0,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m1)) {
                LowerTriMatrix<T1> m1x = m1;
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1x,m0,m0);
            } else {
                MultXM(x,m0=m2);
                MultMM<false>(T(1),m1,m0,m0);
            }
        }
    protected:
        T x;
        const GenLowerTriMatrix<T1>& m1;
        const GenSymMatrix<T2>& m2;
    };

    template <typename T, typename T1, typename T2>
    class ProdSL : public MatrixComposite<T>
    {
    public:
        typedef typename Traits<T>::real_type real_type;
        typedef typename Traits<T>::complex_type complex_type;

        inline ProdSL(
            T _x, const GenSymMatrix<T1>& _m1,
            const GenLowerTriMatrix<T2>& _m2) :
            x(_x), m1(_m1), m2(_m2)
        { TMVAssert(m1.size() == m2.size()); }
        inline ptrdiff_t colsize() const { return m1.size(); }
        inline ptrdiff_t rowsize() const { return m1.size(); }
        inline T getX() const { return x; }
        inline const GenSymMatrix<T1>& getM1() const { return m1; }
        inline const GenLowerTriMatrix<T2>& getM2() const { return m2; }
        inline void assignToM(MatrixView<real_type> m0) const
        {
            TMVAssert(isReal(T()));
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m2)) {
                LowerTriMatrix<T2> m2x = m2;
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2x,m0);
            } else {
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2,m0);
            }
        }
        inline void assignToM(MatrixView<complex_type> m0) const
        {
            TMVAssert(m0.colsize() == colsize());
            TMVAssert(m0.rowsize() == rowsize());
            if (SameStorage(m0,m2)) {
                LowerTriMatrix<T2> m2x = m2;
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2x,m0);
            } else {
                MultXM(x,m0=m1);
                MultMM<false>(T(1),m0,m2,m0);
            }
        }
    protected:
        T x;
        const GenSymMatrix<T1>& m1;
        const GenLowerTriMatrix<T2>& m2;
    };

#define PRODMM ProdSU
#define GENMATRIX1 GenSymMatrix
#define GENMATRIX2 GenUpperTriMatrix
#define PRODXM1 ProdXS
#define PRODXM2 ProdXU
#include "tmv/TMV_AuxProdMM.h"
#include "tmv/TMV_AuxProdMMa.h"
#undef PRODMM
#undef GENMATRIX2
#undef PRODXM2
#define PRODMM ProdSL
#define GENMATRIX2 GenLowerTriMatrix
#define PRODXM2 ProdXL
#include "tmv/TMV_AuxProdMM.h"
#include "tmv/TMV_AuxProdMMa.h"
#undef PRODMM
#undef GENMATRIX1
#undef GENMATRIX2
#undef PRODXM1
#undef PRODXM2

#define PRODMM ProdUS
#define GENMATRIX1 GenUpperTriMatrix
#define GENMATRIX2 GenSymMatrix
#define PRODXM1 ProdXU
#define PRODXM2 ProdXS
#include "tmv/TMV_AuxProdMM.h"
#include "tmv/TMV_AuxProdMMa.h"
#undef PRODMM
#undef GENMATRIX1
#undef PRODXM1
#define PRODMM ProdLS
#define GENMATRIX1 GenLowerTriMatrix
#define PRODXM1 ProdXL
#include "tmv/TMV_AuxProdMM.h"
#include "tmv/TMV_AuxProdMMa.h"
#undef PRODMM
#undef GENMATRIX1
#undef GENMATRIX2
#undef PRODXM1
#undef PRODXM2

    //
    // SymMatrix / % TriMatrix
    //

#define GENMATRIX1 GenSymMatrix
#define GENMATRIX2 GenUpperTriMatrix
#define PRODXM1 ProdXS
#define PRODXM2 ProdXU
#define QUOTXM QuotXU
#define TQUOTMM TransientQuotMU
#define TRQUOTMM TransientRQuotMU
#include "tmv/TMV_AuxTQuotMM.h"
#undef GENMATRIX2
#undef PRODXM2
#undef QUOTXM
#undef TQUOTMM
#undef TRQUOTMM
#define GENMATRIX2 GenLowerTriMatrix
#define PRODXM2 ProdXL
#define QUOTXM QuotXL
#define TQUOTMM TransientQuotML
#define TRQUOTMM TransientRQuotML
#include "tmv/TMV_AuxTQuotMM.h"
#undef GENMATRIX1
#undef GENMATRIX2
#undef PRODXM1
#undef PRODXM2
#undef QUOTXM
#undef TQUOTMM
#undef TRQUOTMM

#define GENMATRIX1 GenUpperTriMatrix
#define GENMATRIX2 GenSymMatrix
#define PRODXM1 ProdXU
#define PRODXM2 ProdXS
#define QUOTXM QuotXS
#define TQUOTMM TransientQuotMS
#define TRQUOTMM TransientRQuotMS
#include "tmv/TMV_AuxTQuotMM.h"
#undef GENMATRIX1
#undef PRODXM1
#define GENMATRIX1 GenLowerTriMatrix
#define PRODXM1 ProdXL
#include "tmv/TMV_AuxTQuotMM.h"
#undef GENMATRIX1
#undef GENMATRIX2
#undef PRODXM1
#undef PRODXM2
#undef QUOTXM
#undef TQUOTMM
#undef TRQUOTMM

}

#undef CT

#endif
