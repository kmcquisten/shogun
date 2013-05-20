#!/usr/bin/env python
from numpy import random,array,sin,round
#from pylab import plot, show, legend

parameter_list=[[20,100,6,10,0.05,1, 1], [10,30,7,9,0.5,0.5, 2]]

def regression_gaussian_process_modular (n=100,n_test=100, \
		x_range=6,x_range_test=10,noise_var=0.5,width=1, seed=1):
		
	from modshogun import RealFeatures, RegressionLabels, GaussianKernel, Math
	try:
		from modshogun import GaussianLikelihood, ZeroMean, \
				ExactInferenceMethod, GaussianProcessRegression
	except ImportError:
		print("Eigen3 needed for Gaussian Processes")
		return
		
	# reproducable results
	random.seed(seed)
	Math.init_random(17)
	
	# easy regression data: one dimensional noisy sine wave
	X=random.rand(1,n)*x_range
	
	X_test=array([[float(i)/n_test*x_range_test for i in range(n_test)]])
	Y_test=sin(X_test)
	Y=sin(X)+random.randn(n)*noise_var
	
	# shogun representation
	labels=RegressionLabels(Y[0])
	feats_train=RealFeatures(X)
	feats_test=RealFeatures(X_test)
	
	# GP specification
	shogun_width=width*width*2
	kernel=GaussianKernel(10, shogun_width)
	zmean = ZeroMean()
	lik = GaussianLikelihood()
	lik.set_sigma(noise_var)
	inf = ExactInferenceMethod(kernel, feats_train, zmean, labels, lik)
	gp = GaussianProcessRegression(inf, feats_train, labels)
	
	# some things we can do
	alpha = inf.get_alpha()
	diagonal = inf.get_diagonal_vector()
	cholesky = inf.get_cholesky()
	
	# inference
	gp.set_return_type(GaussianProcessRegression.GP_RETURN_MEANS)
	mean = gp.apply_regression(feats_test)
	gp.set_return_type(GaussianProcessRegression.GP_RETURN_COV)
	covariance = gp.apply_regression(feats_test)
	
	# plot results
	#plot(X[0],Y[0],'x') # training observations
	#plot(X_test[0],Y_test[0],'-') # ground truth of test
	#plot(X_test[0],mean.get_labels(), '-') # mean predictions of test
	#plot(X_test[0],mean.get_labels()-2*sqrt(covariance.get_labels()), 'm-') # 2*std confidence region
	#plot(X_test[0],mean.get_labels()+2*sqrt(covariance.get_labels()), 'm-') # 2*std confidence region
	#legend(["training", "ground truth", "mean predictions", "confidence"])
	#
	#show()

	return alpha, diagonal, round(covariance.get_labels(),12), round(mean.get_labels(),12), cholesky

if __name__=='__main__':
	print('Gaussian Process Regression')
	regression_gaussian_process_modular(*parameter_list[0])
