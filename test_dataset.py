'''
How to run:
pytest
'''
import numpy as np
import pandas as pd

def test_dataset_size():
    """
    Testing that the dataset size is correct
    """
    df = pd.read_csv("trajectory.csv")
    expected_number_of_rows = 20000
    expected_number_of_columns = 1003
    assert df.shape[0] == expected_number_of_rows
    assert df.shape[1] == expected_number_of_columns

def test_cft_on_dataset():
    """
    Asserts that the work probability distributions meet at the correct point
    """
    df = pd.read_csv("trajectory.csv")
    forward_work = df[df['isForward'] == 1]['w']
    backward_work = df[df['isForward'] == 0]['w']
    p_f, be = np.histogram(forward_work, bins = 40, density = True)
    coords_f = (be[1:] + be[:-1])/2

    p_b, be = np.histogram(backward_work, bins = 40, density = True)
    coords_b = (be[1:] + be[:-1])/2

    # Finding out idx of forward w closest to 0
    idx_f = np.argmin(np.abs(coords_f - 0))

    # Finding out idx of backward w closest to 0
    idx_b = np.argmin(np.abs(-coords_b - 0))

    assert np.abs(p_f[idx_f] - p_b[idx_b]) < 0.015

def test_no_nans():
    """
    Asserts that there are no nans in the dataset
    """
    df = pd.read_csv("trajectory.csv")
    h = df.isna().sum().to_numpy()
    assert np.linalg.norm(h) == 0

if __name__ == "__main__":
    test_dataset_size()
    test_cft_on_dataset()
    test_no_nans()