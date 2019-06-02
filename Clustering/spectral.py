from sklearn.cluster import KMeans, SpectralClustering, DBSCAN
import numpy as np

N = 47
F = 35
K = 4

similarFile = open("./EXPRIDATA/soybean_algo_0.95_1280_2/0/pureRandom.txt")
sourceFile = open("../Partation/soybean_47_35_4/source.txt")
labelFile = open("./EXPRIDATA/soybean_label")


def GetDatapoints():
    lines = sourceFile.readlines()

    datapoints = np.zeros((N, F), dtype=float)

    row = 0
    for line in lines:
        list = line.strip('\n').split(' ')
        datapoints[row] = list[0: N]
        row += 1

    return datapoints


def GetAdjacentMatrix():
    lines = similarFile.readlines()

    similarity = np.zeros((N, N), dtype=float)

    row = 0
    for line in lines:
        list = line.strip('\n').split(' ')
        similarity[row] = list[0: N]
        row += 1

    return similarity


def GetDistance(X1, X2):
    return np.sqrt(np.sum((X1 - X2) ** 2))


def GetSigma(S):
    father = np.zeros(N, dtype=int)
    for i in range(N):
        father[i] = i

    def get_father(x):
        x = int(x)
        if x == father[x]:
            return x
        else:
            father[x] = get_father(father[x])
            return father[x]

    edge = []
    for i in range(N):
        for j in range(N):
            edge.append((S[i, j], i, j))
    edge = sorted(edge, key=lambda x: x[0])

    sigma = 0
    for w, u, v in edge:
        fu = get_father(u)
        fv = get_father(v)
        if fu == fv:
            continue
        father[fu] = fv
        sigma = w
    return sigma


def GetSimilarity(D):
    S = np.zeros((N, N), dtype=float)

    for i in range(N):
        for j in range(N):
            S[i, j] = GetDistance(D[i], D[j])

    sigma = GetSigma(S)
    print(sigma, np.max(S))

    for i in range(N):
        for j in range(N):
            S[i, j] = np.exp(-S[i, j]**2 / (2 * sigma ** 2))
    return S


labelLines = labelFile.read()


def GetClusteringMatrix(predict):

    real = np.zeros((N,), dtype=int)
    real[0:N] = labelLines.split('\n')[0:N]

    accuracy = np.zeros((K, K), dtype=int)

    for i in range(N):
        if predict[i] != -1:
            accuracy[predict[i], real[i]] += 1
    print(accuracy)

# Laplacian = GetLaplacianMatrix()
#
# lam, H = np.linalg.eig(Laplacian)
#
# sp_kmeans = KMeans(n_clusters=K).fit(H)
#
# print(sp_kmeans.labels_)


A = GetAdjacentMatrix()

D = GetDatapoints()
S = GetSimilarity(D)

kmeans = KMeans(n_clusters=K).fit_predict(D)
print(kmeans)
GetClusteringMatrix(kmeans)


dbscan = DBSCAN(eps=3).fit_predict(D)
print(dbscan)
GetClusteringMatrix(dbscan)

spc = SpectralClustering(n_clusters=K, affinity='precomputed').fit(A)
print(spc.labels_)
GetClusteringMatrix(spc.labels_)

spc = SpectralClustering(n_clusters=K, affinity='precomputed').fit(S)
print(spc.labels_)
GetClusteringMatrix(spc.labels_)
