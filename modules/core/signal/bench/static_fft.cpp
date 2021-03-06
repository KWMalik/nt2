//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_BENCH_MODULE "nt2 signal processing with Boost.SIMD - test"

#include <nt2/signal/static_fft.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

#include <boost/simd/sdk/memory/allocator.hpp>
#include <boost/simd/include/functions/scalar/ilog2.hpp>

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#if !defined( BOOST_NO_EXCEPTIONS ) || defined( _MSC_VER )
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#endif // BOOST_NO_EXCEPTIONS


#ifdef __APPLE__
    #include "Accelerate/Accelerate.h" //vDSP.h
#endif // __APPLE__

#ifdef _WIN32
    #include "windows.h"
#endif // _WIN32


#include <cstdlib>
#include <vector>

namespace bench
{
#if defined( BOOST_SIMD_HAS_LRB_SUPPORT ) || defined( BOOST_SIMD_HAS_AVX_SUPPORT )
    typedef double T;
#else //...zzz...cardinal-must-be-4 limitation...
    typedef float T;
#endif // BOOST_SIMD_HAS_LRB_SUPPORT || BOOST_SIMD_HAS_AVX_SUPPORT

    namespace constants
    {
        static std::size_t const minimum_dft_size =    32;
        static std::size_t const maximum_dft_size = 16384;

        static T const test_data_range_minimum = -1;
        static T const test_data_range_maximum = +1;
    } // namespace constants

    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) boost::array<T, constants::maximum_dft_size      > aligned_array;
    typedef BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) boost::array<T, constants::maximum_dft_size/2 + 1> aligned_half_complex_array;

    typedef std::vector<T, boost::simd::memory::allocator<T> > dynamic_aligned_array;

    typedef nt2::static_fft<constants::minimum_dft_size, constants::maximum_dft_size, T> FFT;

    /// \note Portably reproducible pseudo "random" values.
    ///                                       (24.07.2012.) (Domagoj Saric)
    /// \note The used PRNG is much slower than FFT code itself, so we avoid
    /// slowing down the entire benchmark by regenerating the data over and
    /// over.
    ///                                       (11.10.2012.) (Domagoj Saric)
    /// \note NT2Bench configuration has exceptions disabled and Boost.Random
    /// fails to compile then because it uses naked throw statements.
    /// https://svn.boost.org/trac/boost/ticket/7497
    ///                                       (12.10.2012.) (Domagoj Saric)
    class reproducible_random_data_provider
    {
    public:
        reproducible_random_data_provider()
        #if !defined( BOOST_NO_EXCEPTIONS ) || defined( _MSC_VER )
            :
            prng_( 42 )
        #endif // BOOST_NO_EXCEPTIONS
        {
            #if defined( BOOST_NO_EXCEPTIONS ) && !defined( _MSC_VER )
                std::srand( 42 );
            #endif
            randomize( real_data_ );
            randomize( imag_data_ );
        }

        void fill_with_real_data( dynamic_aligned_array & data )
        {
            std::copy( &real_data_[ 0 ], &real_data_[ data.size() ], data.begin() );
        }

        void fill_with_imag_data( dynamic_aligned_array & data )
        {
            std::copy( &imag_data_[ 0 ], &imag_data_[ data.size() ], data.begin() );
        }

        void fill( dynamic_aligned_array & data ) { fill_with_real_data( data ); }

    private:
        void randomize( aligned_array & data )
        {
            #if defined( BOOST_NO_EXCEPTIONS ) && !defined( _MSC_VER )
                BOOST_FOREACH( T & scalar, data ) { scalar = roll<T>( constants::test_data_range_minimum, constants::test_data_range_maximum ); }
            #else
                boost::random::uniform_real_distribution<T> const distribution( constants::test_data_range_minimum, constants::test_data_range_maximum );
                BOOST_FOREACH( T & scalar, data )
                    scalar = distribution( prng_ );
            #endif
        }

    private:
        aligned_array real_data_;
        aligned_array imag_data_;

        boost::random::mt19937 prng_;
    } random_data;

    class complex_fft_test : boost::noncopyable
    {
    public:
        void reset()
        {
            random_data.fill_with_real_data( real_data_ );
            random_data.fill_with_imag_data( imag_data_ );
        }

        std::size_t size() const
        {
            BOOST_ASSERT( real_data_.size() == imag_data_.size() );
            return real_data_.size();
        }

        std::size_t number_of_values() const { return size() * 2; }

    protected:
        complex_fft_test( std::size_t const length )
            :
            real_data_( length ),
            imag_data_( length )
        {
            reset();
        }

        ~complex_fft_test() {}

    protected:
        mutable dynamic_aligned_array real_data_;
        mutable dynamic_aligned_array imag_data_;
    }; // class complex_fft_test


    struct test_fft_forward : complex_fft_test
    {
        test_fft_forward( std::size_t const length ) : complex_fft_test( length ) {}

        void operator()() const { FFT::forward_transform( &real_data_[ 0 ], &imag_data_[ 0 ], size() ); }
    };

    struct test_fft_inverse : complex_fft_test
    {
        test_fft_inverse( std::size_t const length ) : complex_fft_test( length ) {}

        void operator()() const { FFT::inverse_transform( &real_data_[ 0 ], &imag_data_[ 0 ], size() ); }
    };


    class real_fft_test : boost::noncopyable
    {
    public:
        std::size_t size            () const { return real_time_data_.size(); }
        std::size_t number_of_values() const { return size()                ; }

    protected:
        real_fft_test( std::size_t const length )
            :
            real_time_data_     ( length         ),
            real_frequency_data_( length / 2 + 1 ),
            imag_frequency_data_( length / 2 + 1 )
        {}

        ~real_fft_test() {}

    protected:
        /// \note The forward transform uses the frequency data as
        /// output/scratch buffers and the inverse transform uses the
        /// real_time_data as output/scratch buffer, in addition
        /// FFT::real_inverse_transform destroys input data (so it has
        /// to be regenerated). For the said reasons all of the arrays have to
        /// declared mutable
        ///                                   (10.10.2012.) (Domagoj Saric)
        mutable dynamic_aligned_array real_time_data_     ;
        mutable dynamic_aligned_array real_frequency_data_;
        mutable dynamic_aligned_array imag_frequency_data_;
    }; // class real_fft_test


    struct test_fft_real_forward : real_fft_test
    {
        test_fft_real_forward( std::size_t const length ) : real_fft_test( length )
        {
            random_data.fill_with_real_data( real_time_data_ );
        }

        void operator()() const
        {
            FFT::real_forward_transform( &real_time_data_[ 0 ], &real_frequency_data_[ 0 ], &imag_frequency_data_[ 0 ], size() );
        }

        static void reset() {}
    }; // class test_fft_real_forward


    struct test_fft_real_inverse : real_fft_test
    {
        test_fft_real_inverse( std::size_t const length ) : real_fft_test( length ) { reset(); }

        void operator()() const
        {
            FFT::real_inverse_transform( &real_frequency_data_[ 0 ], &imag_frequency_data_[ 0 ], &real_time_data_[ 0 ], size() );
        }

        void reset()
        {
            /// \note FFT::real_inverse_transform destroys input data so it has
            /// to be regenerated.
            ///                               (10.10.2012.) (Domagoj Saric)
            random_data.fill_with_real_data( real_frequency_data_ );
            random_data.fill_with_imag_data( imag_frequency_data_ );
        }
    }; // test_fft_real_inverse


#ifdef __APPLE__
    class apple_fft_test : boost::noncopyable
    {
    protected:
        apple_fft_test( std::size_t const length )
            :
            log2length_  ( boost::simd::ilog2( length )                      ),
            fft_instance_( ::vDSP_create_fftsetup( log2length_, kFFTRadix2 ) )
        {
            if ( !fft_instance_ )
                BOOST_THROW_EXCEPTION( std::bad_alloc() );
        }

        ~apple_fft_test() { ::vDSP_destroy_fftsetup( fft_instance_ ); }

        FFTSetup     instance  () const { return fft_instance_; }
        unsigned int log2length() const { return log2length_  ; }

    private:
        unsigned int const log2length_  ;
        FFTSetup     const fft_instance_;
    }; // class apple_fft_test


    template <FFTDirection direction>
    class apple_complex_fft_test
        :
        public apple_fft_test,
        public complex_fft_test
    {
    public:
        apple_complex_fft_test( std::size_t const length ) : apple_fft_test( length ), complex_fft_test( length ) {}

        void operator()() const
        {
            DSPSplitComplex complex_data( split_data() );
            ::vDSP_fft_zip( instance(), &complex_data, 1, log2length(), direction );
        }

        DSPSplitComplex split_data() const
        {
            DSPSplitComplex complex_data = { &real_data_[ 0 ], &imag_data_[ 0 ] };
            return complex_data;
        }
    }; // class apple_complex_fft_test


    class apple_real_fft_test
        :
        public apple_fft_test,
        public real_fft_test
    {
    protected:
        apple_real_fft_test( std::size_t const length ) : apple_fft_test( length ), real_fft_test( length ) {}

        DSPSplitComplex split_data() const
        {
            DSPSplitComplex complex_data = { &real_frequency_data_[ 0 ], &imag_frequency_data_[ 0 ] };
            return complex_data;
        }
    }; // class apple_real_fft_test

    class apple_real_forward_fft_test : public apple_real_fft_test
    {
    public:
        apple_real_forward_fft_test( std::size_t const length ) : apple_real_fft_test( length ) { random_data.fill_with_real_data( real_time_data_ ); }

        void operator()() const
        {
            DSPSplitComplex split_real_data( split_data() );
            vDSP_ctoz    ( reinterpret_cast<DSPComplex const *>( &real_time_data_[ 0 ] ), 2, &split_real_data, 1, size() / 2 );
            vDSP_fft_zrip( instance(), &split_real_data, 1, log2length(), FFT_FORWARD );
        }

    public:
        static void reset() {}
    }; // class apple_real_forward_fft_test


    class apple_real_inverse_fft_test : public apple_real_fft_test
    {
    public:
        apple_real_inverse_fft_test( std::size_t const length ) : apple_real_fft_test( length ) { reset(); }

        void operator()() const
        {
            DSPSplitComplex split_real_data( split_data() );
            vDSP_fft_zrip( instance(), &split_real_data, 1, log2length(), FFT_INVERSE );
            vDSP_ztoc    ( &split_real_data, 1, reinterpret_cast<DSPComplex *>( &real_time_data_[ 0 ] ), 2, size() / 2 );
        }

    public:
        void reset()
        {
            random_data.fill_with_real_data( real_frequency_data_ );
            random_data.fill_with_imag_data( imag_frequency_data_ );
        }
    }; // class apple_real_fft_test
#endif // __APPLE__

    template <class Benchmark>
    void do_perform_benchmark( char const * const benchmark_name, std::size_t const length )
    {
        typedef nt2::details::cycles_t           cycles_t          ;
        typedef nt2::details::seconds_t          seconds_t         ;
        typedef nt2::unit   ::benchmark_result_t benchmark_result_t;

        double const benchmark_run_time( 0.6 );

        std::printf( "%s (%u):\t\t", benchmark_name, static_cast<unsigned int>( length ) );

        Benchmark benchmark( length );
        benchmark_result_t const benchmark_result( nt2::unit::perform_benchmark( benchmark, benchmark_run_time ) );

        std::printf
        (
            "%.2f cycles/value,\t %.2f microseconds/array\n",
            static_cast<double>( benchmark_result.first ) / benchmark.number_of_values(),
            benchmark_result.second * 1000000
        );
    }

    void do_test()
    {
        for
        (
            std::size_t length( constants::minimum_dft_size );
            length <= constants::maximum_dft_size;
            length *=2
        )
        {
            do_perform_benchmark<test_fft_forward     >( "(nt2) complex forward transform", length );
            do_perform_benchmark<test_fft_inverse     >( "(nt2) complex inverse transform", length );
            do_perform_benchmark<test_fft_real_forward>( "(nt2) real forward transform"   , length );
            do_perform_benchmark<test_fft_real_inverse>( "(nt2) real inverse transform"   , length );

        #ifdef __APPLE__
            do_perform_benchmark<apple_complex_fft_test<FFT_FORWARD> >( "(apple) complex forward transform", length );
            do_perform_benchmark<apple_complex_fft_test<FFT_INVERSE> >( "(apple) complex inverse transform", length );
            do_perform_benchmark<apple_real_forward_fft_test         >( "(apple) real forward transform"   , length );
            do_perform_benchmark<apple_real_inverse_fft_test         >( "(apple) real inverse transform"   , length );
        #endif // __APPLE__
        }
    }
} // namespace bench


//...zzz...nt2 bechmark framework broken...extern "C" int main( int /*argc*/, char * /*argv*/[] )
NT2_TEST_CASE( test_fft )
{
    try
    {
    #ifdef _WIN32
        BOOST_VERIFY( ::SetProcessAffinityMask( ::GetCurrentProcess(),                             1 ) );
        BOOST_VERIFY( ::SetPriorityClass      ( ::GetCurrentProcess(), REALTIME_PRIORITY_CLASS       ) );
        BOOST_VERIFY( ::SetThreadPriority     ( ::GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL ) );
    #endif // _WIN32

        bench::do_test();
        //...zzz...return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        std::puts( e.what() );
        //...zzz...return EXIT_FAILURE;
    }
    catch ( ... )
    {
        std::puts( "Unknown failure." );
        //...zzz...return EXIT_FAILURE;
    }
}
