#include "IGradientMethod.h"
#include "FirstOrderGradientMethod.h"

IGradientMethod* IGradientMethod::create_grad_method(ORDER order, size_t dim, INDimFunction* const func, double tol) {
	switch (order) {
	case ORDER::FIRST:
		return new FirstOrderGradientMethod(dim, func, tol);
	case ORDER::SECOND:
		return nullptr;
	default:
		break;
	}
	return nullptr;
}
