[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['templated cosine.','\par',
                         'see cosine for details'],
         'template' : True ,
         'param_t' : ['used to control accuracy and speed'],   
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['trigonometric'],
         'tpl'   : '<nt2::medium>',   
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                           'extern "C" {extern long double cephes_tanl(long double);}'],                           
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['T(-60)', 'T(60)']],
             'real_' : [['-20*nt2::Pi<T>()', '20*nt2::Pi<T>()']],
             'signed_int_' : [['T(-40)', 'T(40)']],
             'unsigned_int_' : [['T(0)', 'T(40)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Pi<T>()/T(2)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::Pi<T>()/T(4)' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::Zero<T>()' : {'result' : '-nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Pi<T>()/T(2)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Pi<T>()/T(4)' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::cotangent<nt2::medium>(a0)'],
                },
             'property_value' : {
                 'real_' : ['1.0l/::tanl(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : '1.0',
                },
            },
        },
    },
]