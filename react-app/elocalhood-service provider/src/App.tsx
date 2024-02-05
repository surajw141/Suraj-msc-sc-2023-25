import "./App.css";
import Login from "./Login";

function App() {
  return (
    <div
      className="text-white h-[100vh] flex justify-center items-center bg-cover "
      style={{ backgroundImage: `url('../src/assets/bg.jpg')` }}
    >
      <Login />
    </div>
  );
}

export default App;
