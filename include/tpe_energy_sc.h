#pragma once

#include "vert_jacobian.h"
#include "poly_curve_network.h"

namespace LWS {

    enum class TPEPointType {
        Cluster, Point, Edge
    };

    struct TangentMassPoint {
        Vector3 tangent;
        double mass;
        Vector3 point;
        CurveVertex* curvePt;
        CurveVertex* curvePt2;

        TPEPointType type();
    };

    class TPESC {
        public:
        static double tpe_Kf(CurveVertex* i, CurveVertex* j, double alpha, double beta);
        static double tpe_Kf_pts(Vector3 p_x, Vector3 p_y, Vector3 tangent_x, double alpha, double beta);
        
        static double tpe_pair(CurveVertex* i, CurveVertex* j, double alpha, double beta);
        static double tpe_pair_pts(Vector3 p_x, Vector3 p_y, Vector3 tangent_x, double l_x, double l_y, double alpha, double beta);
        static double tpe_total(PolyCurveNetwork* curves, double alpha, double beta);

        static Vector3 tpe_grad_Kf(CurveVertex* i, CurveVertex* j, double alpha, double beta, CurveVertex* wrt);
        static Vector3 tpe_grad_Kf(TangentMassPoint i, CurveVertex* j, double alpha, double beta, CurveVertex* wrt);
        static Vector3 tpe_grad_Kf(CurveVertex* i, TangentMassPoint j, double alpha, double beta, CurveVertex* wrt);

        static Vector3 tpe_grad(CurveVertex* x, CurveVertex* y, double alpha, double beta, CurveVertex* wrt);
        static Vector3 tpe_grad(TangentMassPoint x, CurveVertex* y, double alpha, double beta, CurveVertex* wrt);
        static Vector3 tpe_grad(CurveVertex* x, TangentMassPoint y, double alpha, double beta, CurveVertex* wrt);

        // Projection of (f(i) - f(j)) onto the plane normal to the tangent at i
        static Vector3 proj_normal_plane(CurveVertex* i, CurveVertex* j);
        
        // Gradient of |proj_N|^alpha
        static Vector3 grad_norm_proj_alpha(CurveVertex* i, CurveVertex* j, double alpha, double beta, CurveVertex* wrt);
        static Vector3 grad_norm_proj_alpha(TangentMassPoint i, CurveVertex* j, double alpha, double beta, CurveVertex* wrt);
        static Vector3 grad_norm_proj_alpha(CurveVertex* i, TangentMassPoint j, double alpha, double beta, CurveVertex* wrt);
        static Vector3 grad_norm_proj_num(CurveVertex* i, CurveVertex* j, double alpha, double beta, CurveVertex* wrt, double h);

        // Jacobian of proj_N = ((f(x) - f(y)) - <f(x) - f(y), T> * T)
        static VertJacobian grad_tangent_proj(CurveVertex* i, CurveVertex* j, CurveVertex* wrt);
        static VertJacobian grad_tangent_proj(TangentMassPoint i, CurveVertex* j, CurveVertex* wrt);
        static VertJacobian grad_tangent_proj(CurveVertex* i, TangentMassPoint j, CurveVertex* wrt);
        static VertJacobian grad_tangent_proj_num(CurveVertex* i, CurveVertex* j, CurveVertex* wrt, double h);

        // Gradient of vertex dual length wrt a vertex
        static Vector3 length_wrt_vert(CurveVertex* lengthVert, CurveVertex* wrt);

        // Jacobian of the edge "tangent" (i.e. the edge vector) wrt a vertex
        static VertJacobian edge_tangent_wrt_vert(CurveEdge* edge, CurveVertex* wrtVert);
        // Jacobian of the vertex tangent (average of surrounding edges) wrt a vertex
        static VertJacobian vertex_tangent_wrt_vert(CurveVertex* tangentVert, CurveVertex* wrtVert);
    };
}
