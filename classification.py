import marimo

__generated_with = "0.12.9"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    return (mo,)


@app.cell
def _():
    import pandas as pd
    import numpy as np
    import torch
    from torch.utils.data import Dataset, DataLoader
    import torch.nn as nn
    from torch.nn.utils.rnn import pad_sequence, pack_padded_sequence, pad_packed_sequence
    from sklearn.preprocessing import LabelEncoder
    return (
        DataLoader,
        Dataset,
        LabelEncoder,
        nn,
        np,
        pack_padded_sequence,
        pad_packed_sequence,
        pad_sequence,
        pd,
        torch,
    )


@app.cell
def _(torch):
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Using device: {device}")
    return (device,)


@app.cell
def _(LabelEncoder, device, mo, pad_sequence, pd, torch):
    with mo.persistent_cache("data"):
        data = pd.read_csv('dist/r3-misc-10runs.csv')

        data = data.loc[~data["D0-D7"].isin((00000000, 11111111))]

        time_series = data['Current(uA)'].values
        labels = data['D0-D7'].values

        X = []
        y = []

        current_sequence = []
        for i in range(len(time_series)):
            current_sequence.append(time_series[i])
            if (i + 1) % 10 == 0:
                X.append(torch.tensor(current_sequence, dtype=torch.float32))
                y.append(labels[i])
                current_sequence = []

        X_padded = pad_sequence(X, batch_first=True, padding_value=0)

        label_encoder = LabelEncoder()
        y_encoded = label_encoder.fit_transform(y)

    X_train_tensor = X_padded.to(device)
    y_train_tensor = torch.tensor(y_encoded, dtype=torch.long).to(device)

    train_size = int(0.8 * len(X_train_tensor))
    X_train_tensor, X_test_tensor = X_train_tensor[:train_size], X_train_tensor[train_size:]
    y_train_tensor, y_test_tensor = y_train_tensor[:train_size], y_train_tensor[train_size:]
    return (
        X,
        X_padded,
        X_test_tensor,
        X_train_tensor,
        current_sequence,
        data,
        i,
        label_encoder,
        labels,
        time_series,
        train_size,
        y,
        y_encoded,
        y_test_tensor,
        y_train_tensor,
    )


@app.cell
def _(
    DataLoader,
    Dataset,
    X_test_tensor,
    X_train_tensor,
    device,
    nn,
    np,
    pack_padded_sequence,
    pad_packed_sequence,
    torch,
    y_test_tensor,
    y_train_tensor,
):
    class LSTMModel(nn.Module):
        def __init__(self, input_size=1, hidden_layer_size=50, output_size=1):
            super(LSTMModel, self).__init__()
            self.hidden_layer_size = hidden_layer_size
            self.lstm = nn.LSTM(input_size, hidden_layer_size, batch_first=True).to(device)
            self.fc = nn.Linear(hidden_layer_size, output_size).to(device)

        def forward(self, x, lengths):
            packed_input = pack_padded_sequence(x.to(device), lengths, batch_first=True, enforce_sorted=False)
            packed_output, _ = self.lstm(packed_input)
            lstm_out, _ = pad_packed_sequence(packed_output, batch_first=True)
            last_output = lstm_out[range(lstm_out.size(0)), lengths - 1, :]
            predictions = self.fc(last_output)
            return predictions

    model = LSTMModel(input_size=1, hidden_layer_size=50, output_size=len(np.unique(y_train_tensor.cpu())))
    model = model.to(device)

    loss_fn = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

    class TimeSeriesDataset(Dataset):
        def __init__(self, X, y, device):
            self.X = X
            self.y = y
            self.device = device

        def __len__(self):
            return len(self.X)

        def __getitem__(self, idx):
            return self.X[idx].to(self.device), self.y[idx].to(self.device), len(self.X[idx])

    train_dataset = TimeSeriesDataset(X_train_tensor, y_train_tensor, device)
    test_dataset = TimeSeriesDataset(X_test_tensor, y_test_tensor, device)

    train_loader = DataLoader(train_dataset, batch_size=125_000, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=125_000, shuffle=False)
    return (
        LSTMModel,
        TimeSeriesDataset,
        loss_fn,
        model,
        optimizer,
        test_dataset,
        test_loader,
        train_dataset,
        train_loader,
    )


@app.cell
def _(device, loss_fn, model, optimizer, train_loader):
    def _():
        epochs = 20
        for epoch in range(epochs):
            model.train()
            running_loss = 0.0
            for inputs, _labels, lengths in train_loader:
                inputs, _labels = inputs.to(device), _labels.to(device)
                optimizer.zero_grad()
                outputs = model(inputs.unsqueeze(-1), lengths)
                loss = loss_fn(outputs, _labels)
                loss.backward()
                optimizer.step()
                running_loss += loss.item()
        return print(f"Epoch {epoch+1}/{epochs}, Loss: {running_loss/len(train_loader)}")


    _()
    return


@app.cell
def _(device, model, test_loader, torch):
    def _():
        model.eval()
        correct = 0
        total = 0

        with torch.no_grad():
            for inputs, labels, lengths in test_loader:
                inputs, labels = inputs.to(device), labels.to(device)
                outputs = model(inputs.unsqueeze(-1), lengths)
                _, predicted = torch.max(outputs, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        accuracy = correct / total
        return print(f"Test Accuracy: {accuracy * 100:.2f}%")


    _()
    return


@app.cell
def _(LabelEncoder, device, pad_sequence, pd, torch):
    def x():
        data = pd.read_csv('dist/r4-misc-10runs.csv')

        data = data.loc[~data["D0-D7"].isin((00000000, 11111111))]

        time_series = data['Current(uA)'].values
        labels = data['D0-D7'].values

        X = []
        y = []

        current_sequence = []
        for i in range(len(time_series)):
            current_sequence.append(time_series[i])
            if (i + 1) % 10 == 0:
                X.append(torch.tensor(current_sequence, dtype=torch.float32))
                y.append(labels[i])
                current_sequence = []

        X_padded = pad_sequence(X, batch_first=True, padding_value=0)

        label_encoder = LabelEncoder()
        y_encoded = label_encoder.fit_transform(y)
        return (X_padded, y_encoded)

    X_padded_r4, y_encoded_r4 = x()

    X_train_tensor_r4 = X_padded_r4.to(device)
    y_train_tensor_r4 = torch.tensor(y_encoded_r4, dtype=torch.long).to(device)

    train_size_r4 = int(0.8 * len(X_train_tensor_r4))
    X_train_tensor_r4, X_test_tensor_r4 = X_train_tensor_r4[:train_size_r4], X_train_tensor_r4[train_size_r4:]
    y_train_tensor_r4, y_test_tensor_r4 = y_train_tensor_r4[:train_size_r4], y_train_tensor_r4[train_size_r4:]
    return (
        X_padded_r4,
        X_test_tensor_r4,
        X_train_tensor_r4,
        train_size_r4,
        x,
        y_encoded_r4,
        y_test_tensor_r4,
        y_train_tensor_r4,
    )


@app.cell
def _(
    DataLoader,
    LSTMModel,
    TimeSeriesDataset,
    X_test_tensor_r4,
    X_train_tensor_r4,
    device,
    model,
    nn,
    np,
    torch,
    y_test_tensor_r4,
    y_train_tensor_r4,
):
    model_r4 = LSTMModel(input_size=1, hidden_layer_size=50, output_size=len(np.unique(y_train_tensor_r4.cpu())))
    model_r4 = model.to(device)

    loss_fn_r4 = nn.CrossEntropyLoss()
    optimizer_r4 = torch.optim.Adam(model_r4.parameters(), lr=0.001)

    train_dataset_r4 = TimeSeriesDataset(X_train_tensor_r4, y_train_tensor_r4, device)
    test_dataset_r4 = TimeSeriesDataset(X_test_tensor_r4, y_test_tensor_r4, device)

    train_loader_r4 = DataLoader(train_dataset_r4, batch_size=128, shuffle=True)
    test_loader_r4 = DataLoader(test_dataset_r4, batch_size=128, shuffle=False)
    return (
        loss_fn_r4,
        model_r4,
        optimizer_r4,
        test_dataset_r4,
        test_loader_r4,
        train_dataset_r4,
        train_loader_r4,
    )


@app.cell
def _(
    device,
    loss_fn_r4,
    model_r4,
    optimizer_r4,
    train_loader,
    train_loader_r4,
):
    def _():
        epochs = 30
        for epoch in range(epochs):
            model_r4.train()
            running_loss = 0.0
            for inputs, _labels, lengths in train_loader_r4:
                inputs, _labels = inputs.to(device), _labels.to(device)
                optimizer_r4.zero_grad()
                outputs = model_r4(inputs.unsqueeze(-1), lengths)
                loss = loss_fn_r4(outputs, _labels)
                loss.backward()
                optimizer_r4.step()
                running_loss += loss.item()
        return print(f"Epoch {epoch+1}/{epochs}, Loss: {running_loss/len(train_loader)}")


    _()
    return


@app.cell
def _(device, model_r4, np, test_loader_r4, torch, y_train_tensor_r4):
    def _():
        model_r4.eval()
        correct = 0
        total = 0

        with torch.no_grad():
            for inputs, labels, lengths in test_loader_r4:
                inputs, labels = inputs.to(device), labels.to(device)
                outputs = model_r4(inputs.unsqueeze(-1), lengths)
                _, predicted = torch.max(outputs, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        accuracy = correct / total
        return print(f"Test Accuracy: {accuracy * 100:.2f}%")


    _()
    print(len(np.unique(y_train_tensor_r4.cpu())))
    return


if __name__ == "__main__":
    app.run()
